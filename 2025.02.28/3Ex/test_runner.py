import json
import subprocess
import os
import time
import platform
import re
from colorama import Fore, Style, init

# Enable color support in Windows
init(autoreset=True)

def color_text(text, color):
    """Returns colored text"""
    return color + text + Style.RESET_ALL

class TestCase:
    """Represents a single test case"""
    def __init__(self, x, c, text, expected, res, p=None, debug=False, name=None):
        self.x = x
        self.c = c
        self.text = text
        self.expected = expected
        self.res = res
        self.p = p
        self.debug = debug
        self.name = name if name else str(c)  # Используем c, если name отсутствует

    def get_num_lines(self):
        """Returns the number of lines in the input text (n)"""
        return self.text.count("\n") + 1  # +1, чтобы учесть последнюю строку

    def should_fail(self):
        """Checks if the test expects a failure"""
        return self.expected.lower() == "fall"

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

def parse_sorted_output(output):
    """Extracts the second print_array output from program output"""
    parts = output.split("New array:\n")
    if len(parts) > 1:
        sorted_array = parts[1].strip().split("\n")
        sorted_array = sorted_array[:-1]  # Убираем последнюю строку (Task = ... Res = ... Elapsed = ...)
        return "\n".join(sorted_array)
    return ""

def check_res(output, expected_res):
    """Checks if Res matches expected value"""
    match = re.search(r"Res\s*=\s*(-?\d+)", output)
    if match:
        res_value = int(match.group(1))
        if res_value != expected_res:
            print(color_text(f"[FAIL] Test failed: Res = {res_value} (expected {expected_res})", Fore.RED))
            return False
    return True

def run_test(test_suite, test):
    """Runs the program and checks its result"""
    exe, filename = test_suite.exe, test_suite.filename
    n = test.get_num_lines()  # Auto-count lines in input
    p = test.p if test.p is not None else n  # Default p = n

    # Write input data to a file (Ensure last line has \n)
    with open(filename, "w", encoding="utf-8") as f:
        text = test.text.rstrip() + "\n"  # Если нет \n в конце, добавляем
        f.write(text)

    # Windows fix: remove './' for executables
    cmd = [exe, test.x, str(test.c), str(n), str(p), filename]
    if test.debug:
        cmd.append("DEBUG")

    # Run the program
    result = run_command(cmd)

    # Check if test expected failure
    if test.should_fail():
        if result and result.returncode != 0:
            print(color_text(f"[PASS] Test '{test.name}' correctly failed (expected crash).", Fore.GREEN))
        else:
            print(color_text(f"[FAIL] Test '{test.name}' should have failed but did not.", Fore.RED))
        return

    # Extract sorted array output
    sorted_output = parse_sorted_output(result.stdout) if result else None

    # Check Res value
    if not check_res(result.stdout, test.res):
        return

    # Check result
    if sorted_output == test.expected:
        print(color_text(f"[PASS] Test '{test.name}' passed.", Fore.GREEN))
    else:
        print(color_text(f"[FAIL] Test '{test.name}' failed.", Fore.RED))
        print(f"Expected:\n{test.expected}")
        print(f"Got:\n{sorted_output}")
        if test.debug:
            print(color_text("[DEBUG] Full Program Output:", Fore.YELLOW))
            print(result.stdout)

    # Cleanup test files
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
