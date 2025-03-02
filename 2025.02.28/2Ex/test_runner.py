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
    def __init__(self, c, a, b, expected):
        self.c = c
        self.a = a
        self.b = b
        self.expected = expected

class TestSuite:
    """Handles loading and running test cases"""
    def __init__(self, config_file):
        self.config = self.load_config(config_file)
        self.exe = self.config["exe"]
        self.filename_a = self.config["filename_a"]
        self.filename_b = self.config["filename_b"]
        self.tests = [TestCase(**test) for test in self.config["tests"]]

    @staticmethod
    def load_config(filename):
        """Loads test cases from JSON"""
        with open(filename, "r", encoding="utf-8") as f:
            return json.load(f)

def run_command(cmd):
    """Runs a shell command and handles errors"""
    result = subprocess.run(cmd, capture_output=True, text=True, shell=True)
    return result

def count_lines(filename):
    """Counts the number of non-empty lines in a file"""
    try:
        with open(filename, "r", encoding="utf-8") as f:
            return sum(1 for line in f if line.strip())
    except FileNotFoundError:
        print(color_text(f"[ERROR] File {filename} not found.", Fore.RED))
        return 0

def run_test(test_suite, test):
    """Runs the program and checks its result"""
    exe = test_suite.exe
    filename_a = test_suite.filename_a
    filename_b = test_suite.filename_b

    # Write input arrays to files
    with open(filename_a, "w", encoding="utf-8") as fa:
        fa.write(test.a)
    with open(filename_b, "w", encoding="utf-8") as fb:
        fb.write(test.b)
    
    # Calculate n and m correctly
    n = count_lines(filename_a)
    m = count_lines(filename_b)
    pa = n
    pb = m
    
    # Debug output to check file contents
    print(color_text(f"[DEBUG] a.txt content:\n{open(filename_a).read()}", Fore.CYAN))
    print(color_text(f"[DEBUG] b.txt content:\n{open(filename_b).read()}", Fore.CYAN))
    print(color_text(f"[DEBUG] Calculated n = {n}, m = {m}", Fore.CYAN))
    
    # Ensure correct execution command on Windows
    exe_cmd = exe if platform.system() == "Windows" else f"./{exe}"
    
    # Form command-line arguments as a list
    cmd = [exe_cmd, str(test.c), str(n), str(pa), filename_a, str(m), str(pb), filename_b]
    print(color_text(f"[DEBUG] Running command: {' '.join(cmd)}", Fore.CYAN))
    
    # Run program
    result = run_command(cmd)
    if result.returncode != 0:
        print(color_text(f"[ERROR] Test failed to execute: {' '.join(cmd)}", Fore.RED))
        print(color_text(f"[EXIT CODE]: {result.returncode}", Fore.YELLOW))
        print(color_text(f"[STDOUT]: {result.stdout}", Fore.YELLOW))
        print(color_text(f"[STDERR]: {result.stderr}", Fore.YELLOW))
        return
    
    # Extract relevant output
    output_lines = result.stdout.split("\n")
    try:
        start_index = output_lines.index("New array:") + 1
        end_index = next(i for i, line in enumerate(output_lines) if "Task" in line)
        output = "\n".join(output_lines[start_index:end_index])
    except (ValueError, IndexError):
        print(color_text(f"[FAIL] Could not parse output correctly.", Fore.RED))
        return
    
    # Validate output
    if output == test.expected:
        print(color_text(f"[PASS] Test passed.", Fore.GREEN))
    else:
        print(color_text(f"[FAIL] Test failed.", Fore.RED))
        print(color_text(f"Expected:\n{test.expected}", Fore.YELLOW))
        print(color_text(f"Got:\n{output}", Fore.YELLOW))
    
    # Cleanup files
    for file in [filename_a, filename_b]:
        try:
            os.remove(file)
        except FileNotFoundError:
            print(color_text(f"[WARNING] Could not delete {file}, may be locked.", Fore.MAGENTA))

def main():
    print(color_text("[CLEAN] Cleaning project...", Fore.MAGENTA))
    run_command(["make", "clean"])
    print(color_text("[BUILD] Compiling project...", Fore.MAGENTA))
    run_command(["make"])

    test_suite = TestSuite("test_cases.json")
    for test in test_suite.tests:
        run_test(test_suite, test)
    
    print(color_text("[CLEAN] Final cleanup...", Fore.MAGENTA))
    run_command(["make", "clean"])

if __name__ == "__main__":
    main()
