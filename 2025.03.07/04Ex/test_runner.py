import json
import subprocess
import os
import time
import platform
import re
import signal
from colorama import Fore, Style, init

# Enable color support in Windows
init(autoreset=True)

def color_text(text, color):
    """Returns colored text"""
    return color + text + Style.RESET_ALL

def cleanup_and_exit():
    """Handles cleanup on Ctrl+C or forced exit"""
    print(color_text("\n[ABORT] Operation interrupted. Cleaning up...", Fore.RED))
    run_command("make clean")
    exit(1)

# Register Ctrl+C handler
signal.signal(signal.SIGINT, lambda sig, frame: cleanup_and_exit())

class TestCase:
    """Represents a single test case"""
    def __init__(self, k, matrix=None, n=None, p=None, debug=False, name=None):
        self.k = k
        self.matrix = matrix
        self.n = n
        self.p = p
        self.debug = debug
        self.name = name if name else f"Test k={k}, n={n if n else 'auto'}, p={p if p else 'auto'}"

        # Compute `n` if missing and `k == 0`
        if self.k == 0 and not self.n and self.matrix:
            self.n = len(self.matrix.strip().split("\n"))

        # Compute `p`
        self.p = self.p if self.p else self.n

    def validate_inputs(self):
        """Ensures input values are valid"""
        if self.k < 0 or (self.k == 0 and not self.matrix):
            print(color_text(f"[ERROR] Invalid test parameters: {self.name}", Fore.RED))
            return False
        return True

class TestSuite:
    """Handles loading and running test cases"""
    def __init__(self, config_file):
        self.config = self.load_config(config_file)
        self.exe = self.config["exe"]
        self.filename = self.config["filename"]
        self.tests = [TestCase(**test) for test in self.config["tests"]]

    @staticmethod
    def load_config(filename):
        """Loads test cases from JSON"""
        with open(filename, "r", encoding="utf-8") as f:
            return json.load(f)

def run_command(cmd, exit_on_error=False):
    """Runs a shell command and handles errors"""
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
    """Waits for the executable file to appear after compilation"""
    print(color_text(f"[WAIT] Waiting for {exe} to be compiled...", Fore.YELLOW))
    while not os.path.exists(exe):
        time.sleep(0.1)  # Reduce CPU usage
    print(color_text(f"[READY] {exe} compiled successfully.", Fore.GREEN))

def format_matrix(matrix):
    """Formats a matrix to match `printf("%10.3e")` output"""
    formatted = []
    for row in matrix.strip().split("\n"):
        formatted.append(" ".join(f"{float(num):10.3e}" for num in row.split()))
    return "\n".join(formatted)

def result_matrix_output(output):
    parts = output.split("Result matrix:\n")
    if len(parts) > 1:
        matrix_lines = parts[1].strip().split("\n")
        return format_matrix("\n".join(matrix_lines[:-1]))
    return ""

def initial_matrix_output(output):
    parts = output.split("Initial matrix:\n")
    if len(parts) > 1:
        parts = parts[1].split("Result")
        matrix_lines = parts[0].strip().split("\n")
        return format_matrix("\n".join(matrix_lines))
    return ""

def symmetric_matrix(matrix):
    rows = [list(map(float, row.split())) for row in matrix.strip().split("\n")]
    symmetrize =  [[((rows[i][j] + rows[j][i]) / 2) for j in range(len(rows[i]))] for i in range(len(rows))]
    return "\n".join(" ".join(f"{float(num):10.3e}" for num in row) for row in symmetrize)

def run_test(test_suite, test):
    """Runs the program and checks its result"""
    if not test.validate_inputs():
        return

    exe, filename = test_suite.exe, test_suite.filename

    # If matrix is given, write it to the file
    if test.k == 0 and test.matrix:
        with open(filename, "w", encoding="utf-8") as f:
            f.write(format_matrix(test.matrix.strip()) + "\n")

    cmd = [exe, str(test.n), str(test.p), str(test.k)]
    if test.k == 0:
        cmd.append(filename)

    # Run the program
    result = run_command(cmd)

    # Extract both initial and result matrices
    initial_matrix = initial_matrix_output(result.stdout)
    result_matrix = result_matrix_output(result.stdout)

    expected_transposed = symmetric_matrix(initial_matrix)

    if result_matrix.strip() != expected_transposed.strip():
        print(color_text(f"[FAIL] Test '{test.name}' matrix mismatch.", Fore.RED))
        print(f"Expected:\n{expected_transposed}")
        print(f"Got:\n{result_matrix}")
        return

    print(color_text(f"[PASS] Test '{test.name}' passed.", Fore.GREEN))
    
    if test.k == 0:
         # Cleanup test file
        try:
            os.remove(filename)
        except (FileNotFoundError, PermissionError):
            print(color_text(f"[WARNING] Could not delete {filename}, Windows may be locking it.", Fore.RED))

   
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
