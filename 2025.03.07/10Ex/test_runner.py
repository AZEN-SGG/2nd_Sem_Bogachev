import json
import subprocess
import os
import time
import platform
import re
import signal
from colorama import Fore, Style, init
import math

init(autoreset=True)  # Enable color support in Windows

def color_text(text, color):
    """Returns colored text."""
    return color + text + Style.RESET_ALL

def cleanup_and_exit():
    """Handles cleanup on Ctrl+C or forced exit."""
    print(color_text("\n[ABORT] Operation interrupted. Cleaning up...", Fore.RED))
    run_command("make clean")
    exit(1)

# Register Ctrl+C handler
signal.signal(signal.SIGINT, lambda sig, frame: cleanup_and_exit())

class TestCase:
    """
    Represents a single test case for matrix multiplication:
      n, m, k: dimensions
      p: number of displayed rows/columns
      kA: formula for matrix A (0 => read from file)
      kB: formula for matrix B (0 => read from file)
      matrix_a, matrix_b: text for input files if kA=0 or kB=0
      name: optional test name
    """
    def __init__(self,
                 n=None,
                 m=None,
                 k=None,
                 p=None,
                 kA=None,
                 kB=None,
                 matrix_a=None,
                 matrix_b=None,
                 name=None):

        # Required parameters
        self.n = n
        self.m = m
        self.k = k
        self.kA = kA
        self.kB = kB

        # Possibly missing p => p = max(n, m, k)
        self.p = p

        # If kA=0 => matrix_a must be provided
        self.matrix_a = matrix_a
        # If kB=0 => matrix_b must be provided
        self.matrix_b = matrix_b

        # If no name => auto
        self.name = name if name else f"Test (n={n}, m={m}, k={k}, kA={kA}, kB={kB})"

        # Fix up the dimension logic:
        # n not required if kA=0 => read from matrix_a lines
        # m not required if kA=0 => read from matrix_a columns or lines from matrix_b
        # k not required if kB=0 => read from matrix_b columns
        # p => default = max(n,m,k)
        self._fix_dimensions()

    def _fix_dimensions(self):
        """Resolve missing n, m, k, p from matrix files if needed."""
        # If kA=0 => we must figure out n,m from matrix_a
        if self.kA == 0 and self.matrix_a:
            lines_a = self.matrix_a.strip().split("\n")
            _n = len(lines_a)
            _m = len(lines_a[0].split()) if _n > 0 else 0
            if not self.n:
                self.n = _n
            if not self.m:
                self.m = _m

        # If kB=0 => figure out dimensions from matrix_b
        if self.kB == 0 and self.matrix_b:
            lines_b = self.matrix_b.strip().split("\n")
            _m2 = len(lines_b)
            _k = len(lines_b[0].split()) if _m2 > 0 else 0
            if not self.m:
                self.m = _m2
            if not self.k:
                self.k = _k

        # If p not specified => p = max(n,m,k)
        if not self.p:
            self.p = max(self.n, self.m, self.k)

    def validate_inputs(self):
        """Check minimal validity for the test."""
        if self.kA is None or self.kB is None:
            print(color_text(f"[ERROR] Missing kA/kB in test '{self.name}'", Fore.RED))
            return False
        if self.kA == 0 and not self.matrix_a:
            print(color_text(f"[ERROR] kA=0 but no matrix_a provided: {self.name}", Fore.RED))
            return False
        if self.kB == 0 and not self.matrix_b:
            print(color_text(f"[ERROR] kB=0 but no matrix_b provided: {self.name}", Fore.RED))
            return False
        if any(x is None for x in [self.n, self.m, self.k]):
            print(color_text(f"[ERROR] Dimensions not resolved in test '{self.name}'", Fore.RED))
            return False
        return True

class TestSuite:
    """Loads the config, builds TestCase objects, tracks exe / files."""
    def __init__(self, config_file):
        self.config = self.load_config(config_file)
        self.exe = self.config["exe"]
        # fA / fB are file names for matrix A and B input
        self.fA = self.config["fA"]
        self.fB = self.config["fB"]
        self.tests = [TestCase(**test) for test in self.config["tests"]]

    @staticmethod
    def load_config(filename):
        with open(filename, "r", encoding="utf-8") as f:
            return json.load(f)

def run_command(cmd, exit_on_error=False):
    """Runs shell command with errors captured."""
    try:
        result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
        return result
    except subprocess.CalledProcessError as e:
        print(color_text(f"[ERROR] Command failed: {cmd}", Fore.RED))
        print(e.stderr)
        if exit_on_error:
            exit(1)
        return None

def wait_for_executable(exe):
    """Wait for the .exe to appear after compilation."""
    print(color_text(f"[WAIT] Waiting for {exe} to be compiled...", Fore.YELLOW))
    while not os.path.exists(exe):
        time.sleep(0.1)
    print(color_text(f"[READY] {exe} compiled successfully.", Fore.GREEN))

def format_matrix(text):
    """
    Convert a raw matrix text (e.g. '1 2 3\n4 5 6') into a string with each
    value formatted as '%10.3e' to match the program's output.
    """
    lines = text.strip().split("\n")
    out_lines = []
    for line in lines:
        nums = line.split()
        fmt_nums = [f"{float(n):10.3e}" for n in nums]
        out_lines.append(" ".join(fmt_nums))
    return "\n".join(out_lines)

def parse_matrix_output(output, label):
    """
    Extracts a matrix from the test program's output, e.g.:
      "Initial matrix A:\n ... \n... \nInitial vector b:"
    If not found, returns ''.
    """
    pattern = rf"{label}:\s*\n(.*?)\n[a-zA-Z]"  # match until next label or next letter
    match = re.search(pattern, output, flags=re.DOTALL)
    if match:
        raw = match.group(1).strip()
        return raw
    return ""

def matrix_multiply(A, B, n, m, k):
    """
    Multiply A(n×m) by B(m×k) => C(n×k).
    A, B are lists of lists (floats).
    Returns list of lists for C.
    """
    # Initialize C
    C = [[0.0]*k for _ in range(n)]
    for i in range(n):
        for j in range(k):
            val = 0.0
            for z in range(m):
                val += A[i][z]*B[z][j]
            C[i][j] = val
    return C

def parse_matrix_lines(matrix_str):
    """
    Convert matrix string (with ' %10.3e') lines => list of lists (floats).
    """
    lines = matrix_str.strip().split("\n")
    mat = []
    for ln in lines:
        row = ln.strip().split()
        # row = ['1.000e+000','2.000e+000',...]
        mat.append([float(x) for x in row])
    return mat

def mat_to_str(mat):
    """
    Convert a list-of-lists (floats) to the string with '%10.3e' format.
    """
    lines = []
    for row in mat:
        lines.append(" ".join(f"{val:10.3e}" for val in row))
    return "\n".join(lines)

def generate_matrix(n, m, k_formula):
    """
    If k_formula !=0 => generate an n×m matrix using formula f(k_formula, n, m, i, j).
    """
    def f(kf, n, m, i, j):
        if kf == 1:
            return max(n, m) - max(i, j) + 1
        elif kf == 2:
            return max(i, j)
        elif kf == 3:
            return abs(i-j)
        elif kf == 4:
            return 1.0/(i+j-1) if (i+j-1)!=0 else 0
        return 0

    mat = []
    for i in range(1, n+1):
        row = []
        for j in range(1, m+1):
            row.append(f(k_formula, n, m, i, j))
        mat.append(row)
    return mat

import math

def print_matrix_mismatch(expected, actual, matrix_name, test_name):
    """
    Печатает подробную информацию о несовпадении двух матриц.
    expected, actual: list-of-lists (float values)
    matrix_name: как назвать матрицу (например, "Matrix A" или "Matrix B")
    test_name: имя теста или любая другая справочная информация
    """
    print(f"[FAIL] {test_name} - mismatch in {matrix_name}")
    
    # Полный вывод матриц
    print(f"\n{matrix_name} (EXPECTED):")
    print(_matrix_to_str(expected))
    print(f"\n{matrix_name} (ACTUAL):")
    print(_matrix_to_str(actual))

    # Если есть разница в размере — выводим
    if len(expected) != len(actual) or any(len(e) != len(a) for e,a in zip(expected, actual)):
        print("\n[INFO] Shape mismatch.")
        return

    # Вывод различий поэлементно
    print("\n[INFO] Differences (index, expected, got):")
    found_diff = False
    for i, (rowE, rowA) in enumerate(zip(expected, actual)):
        for j, (valE, valA) in enumerate(zip(rowE, rowA)):
            if not math.isclose(valE, valA, rel_tol=1e-3, abs_tol=1e-4):
                found_diff = True
                print(f"  [{i},{j}] {valE:10.3e} != {valA:10.3e}")
    if not found_diff:
        print("  No elementwise differences found (shape was likely mismatched or zero-size).")

def _matrix_to_str(matrix):
    """
    Вспомогательная функция для форматирования матрицы:
    печатает элементы в стиле '%10.3e' (как в тестируемой программе).
    """
    lines = []
    for row in matrix:
        line = " ".join(f"{val:10.3e}" for val in row)
        lines.append(line)
    return "\n".join(lines)

def print_matrix_shape_mismatch(expected, actual, matrix_name, test_name):
    """
    Выводит информацию при несовпадении размеров (shape) двух матриц.
    expected, actual: list-of-lists (float values)
    matrix_name: как назвать матрицу (например, "Matrix A" или "Matrix B")
    test_name: имя теста или любая другая справочная информация
    """
    print(f"[FAIL] {test_name} - mismatch shape in {matrix_name}")

    len_expected = len(expected)
    len_actual   = len(actual)
    print(f"  {matrix_name} (EXPECTED) shape: {len_expected} x {len(expected[0]) if len_expected>0 else 0}")
    print(f"  {matrix_name} (ACTUAL)   shape: {len_actual} x {len(actual[0]) if len_actual>0 else 0}")

    # Если ещё неясно, где именно несоответствие,
    # можно вывести детальнее по каждой строке:
    if len_expected == len_actual:
        for i, (rowE, rowA) in enumerate(zip(expected, actual)):
            if len(rowE) != len(rowA):
                print(f"  Row {i} length mismatch: {len(rowE)} != {len(rowA)}")

def run_test(test_suite, test):
    """Main test logic."""
    if not test.validate_inputs():
        return

    # Prepare matrix A, B => write to fA, fB if kA=0 or kB=0
    # Or generate them if kA!=0 / kB!=0
    # 1) build/format matrix A => string => write to fA if kA=0
    # 2) build/format matrix B => string => write to fB if kB=0

    fA = test_suite.fA
    fB = test_suite.fB

    # Build A
    if test.kA == 0 and test.matrix_a:
        # Write matrix_a (formatted) to fA
        with open(fA, "w", encoding="utf-8") as fa:
            fa.write(format_matrix(test.matrix_a) + "\n")
        # Also parse it as 2D float array for local multiplication
        A_list = parse_matrix_lines(format_matrix(test.matrix_a))
    else:
        # generate
        A_list = generate_matrix(test.n, test.m, test.kA)

    # Build B
    if test.kB == 0 and test.matrix_b:
        with open(fB, "w", encoding="utf-8") as fb:
            fb.write(format_matrix(test.matrix_b) + "\n")
        B_list = parse_matrix_lines(format_matrix(test.matrix_b))
    else:
        B_list = generate_matrix(test.m, test.k, test.kB)

    # -- Build command line --
    # n m k p kA [fA_if kA=0] kB [fB_if kB=0]
    cmd_list = [test_suite.exe,
                str(test.n), str(test.m), str(test.k),
                str(test.p),
                str(test.kA)]
    if test.kA==0:
        cmd_list.append(fA)
    cmd_list.append(str(test.kB))
    if test.kB==0:
        cmd_list.append(fB)

    cmd = " ".join(cmd_list)

    # Run the program
    result = run_command(cmd)

    # 2) Extract matrix A => "Initial matrix A:"
    #    matrix B => "Initial vector b:"
    #    matrix C => "Result vector c:"
    output = result.stdout
    initA_str = parse_matrix_output(output, "Initial matrix A")
    initB_str = parse_matrix_output(output, "Initial vector b")
    resC_str  = parse_matrix_output(output, "Result vector c")

    # Convert them to list-of-lists
    initA_list = parse_matrix_lines(format_matrix(initA_str))
    initB_list = parse_matrix_lines(format_matrix(initB_str))
    resC_list  = parse_matrix_lines(format_matrix(resC_str))

    # 3) Compare initA_list with A_list (both 2D arrays)
    #    Compare initB_list with B_list
    #    Then multiply A_list * B_list => localC_list
    #    Compare localC_list with resC_list
    # Make sure shapes match.

    # Compare shapes for A
    if len(initA_list) != len(A_list) or any(len(rowA) != len(rowB) for rowA, rowB in zip(initA_list, A_list)):
        print(color_text(f"[FAIL] {test.name} - mismatch shape in A", Fore.RED))
        print_matrix_shape_mismatch(A_list, initA_list, "Matrix A", test.name)
        return

    # Compare each element
    for rowA, rowB in zip(initA_list, A_list):
        for valA, valB in zip(rowA, rowB):
            if not math.isclose(valA, valB, rel_tol=1e-3, abs_tol=1e-4):
                print(color_text(f"[FAIL] {test.name} - mismatch in matrix A", Fore.RED))
                print_matrix_mismatch(A_list, initA_list, "Matrix A", test.name)
                return

    # Compare shapes for B
    if len(initB_list) != len(B_list) or any(len(rA) != len(rB) for rA, rB in zip(initB_list, B_list)):
        print(color_text(f"[FAIL] {test.name} - mismatch shape in B", Fore.RED))
        print_matrix_shape_mismatch(B_list, initB_list, "Matrix B", test.name)
        return

    for rowA, rowB in zip(initB_list, B_list):
        for valA, valB in zip(rowA, rowB):
            if not math.isclose(valA, valB, rel_tol=1e-3, abs_tol=1e-4):
                print(color_text(f"[FAIL] {test.name} - mismatch in matrix B", Fore.RED))
                print_matrix_mismatch(B_list, initB_list, "Matrix B", test.name)
                return

    # Multiply local
    localC_list = matrix_multiply(A_list, B_list, test.n, test.m, test.k)

    # Compare shape with resC_list
    if len(resC_list) != len(localC_list) or any(len(aRow) != len(bRow) for aRow,bRow in zip(resC_list, localC_list)):
        print(color_text(f"[FAIL] {test.name} - mismatch shape in C", Fore.RED))
        print_matrix_shape_mismatch(localC_list, resC_list, "Matrix A", test.name)
        return

    # Compare each element
    for rC, lC in zip(resC_list, localC_list):
        for vC, vLoc in zip(rC, lC):
            if not math.isclose(vC, vLoc, rel_tol=1e-3, abs_tol=1e-4):
                print(color_text(f"[FAIL] {test.name} - mismatch in matrix C", Fore.RED))
                print_matrix_mismatch(resC_list, localC_list, "Matrix C", test.name)
                return

    print(color_text(f"[PASS] {test.name}", Fore.GREEN))

    # Cleanup
    if test.kA==0:
        try:
            os.remove(test_suite.fA)
        except:
            pass
    if test.kB==0:
        try:
            os.remove(test_suite.fB)
        except:
            pass

def main():
    print(color_text("[CLEAN] Cleaning project...", Fore.BLUE))
    run_command("make clean", exit_on_error=True)

    print(color_text("[BUILD] Compiling project...", Fore.BLUE))
    run_command("make", exit_on_error=True)

    test_suite = TestSuite("test_cases.json")
    wait_for_executable(test_suite.exe)

    for test in test_suite.tests:
        run_test(test_suite, test)

    print(color_text("[CLEAN] Final cleanup...", Fore.BLUE))
    run_command("make clean")

if __name__ == "__main__":
    main()
