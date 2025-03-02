import json
import subprocess
import os
import time
import platform
from colorama import Fore, Style, init

# Enable color support in Windows
init(autoreset=True)

def color_text(text, color):
    """Returns colored text"""
    return color + text + Style.RESET_ALL

class TestCase:
    """Represents a single test case"""
    def __init__(self, s, text, expected):
        self.s = s
        self.text = text
        self.expected = expected

    def should_fail(self):
        """Checks if the test expects a failure"""
        return self.expected.lower() == "fall"

class TestSuite:
    """Handles loading and running test cases"""
    def __init__(self, config_file):
        self.config = self.load_config(config_file)
        self.exe = self.config["exe"]
        self.f_in = self.config["f_in"]
        self.f_out = self.config["f_out"]
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

def run_test(test_suite, test):
    """Runs the program and checks its result"""
    exe, f_in, f_out = test_suite.exe, test_suite.f_in, test_suite.f_out

    # Write input data to a file
    with open(f_in, "w", encoding="utf-8") as f:
        f.write(test.text)

    # Windows fix: remove './' for executables
    cmd = [exe, f_in, f_out, test.s] if platform.system() == "Windows" else [f"./{exe}", f_in, f_out, test.s]

    # Run the program
    result = run_command(cmd)

    # Check if test expected failure
    if test.should_fail():
        if result and result.returncode != 0:
            print(color_text(f"[PASS] Test '{test.s}' correctly failed (expected crash).", Fore.GREEN))
        else:
            print(color_text(f"[FAIL] Test '{test.s}' should have failed but did not.", Fore.RED))
        return

    # Read output file
    try:
        with open(f_out, "r", encoding="utf-8") as f:
            output = f.read()
    except FileNotFoundError:
        output = None

    # Check result
    if output == test.expected:
        print(color_text(f"[PASS] Test '{test.s}' passed.", Fore.GREEN))
    else:
        print(color_text(f"[FAIL] Test '{test.s}' failed.", Fore.RED))
        print(f"Expected:\n{test.expected}")
        print(f"Got:\n{output}")

    # Cleanup test files
    for file in [f_in, f_out]:
        try:
            os.remove(file)
        except (FileNotFoundError, PermissionError):
            print(color_text(f"[WARNING] Could not delete {file}, Windows may be locking it.", Fore.RED))

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
