"""
The following python "script" can be ran to help collect 
process time for multiple iterations. External scripts like this are 
common in research.    


Sample execution would be to write out the standard out (print) to a file. For example

python3 test_runner.py 30 csv  > pascal_run.csv

python3 test_runner.py 30 > pascal_table.md
"""

import subprocess
import sys
import csv

EXEC = ["./pascal.exe"]
COMMON_ARG_FORMAT = "{n} {type}"
TIMEOUT = 60
OUT_DEFAULT = "pascal_run.csv"
OUT_FILE_TIME = "timings_"
OUT_FILE_OPS = "ops_"
CSV_HEADER = "N,Iterative,Dynamic Programming,Recursive"


class RecursionTimeoutError(Exception):
    pass


def run_single(n: int, typ: int) -> dict:
    """Run a single instance collecting the values into a dictionary
    with two tuples, one for timings and one for operations

    Args:
        n (int): the row to generate
        typ (int): the type of algorithm to use

    Returns:
        float: the time it took, or nan if TIMEOUT is reached first
    """
    args = COMMON_ARG_FORMAT.format(n=n, type=typ)
    try:
        results = subprocess.run(
            EXEC + args.split(), timeout=TIMEOUT, capture_output=True, text=True
        )
    except subprocess.TimeoutExpired:
        raise RecursionTimeoutError(f"Timeout of {TIMEOUT} seconds reached for {args}")

    if results.returncode != 0:
        raise Exception(f"Error running {args}: {results.stderr}")

    results_line = results.stdout.strip().split(",")
    timings = []
    operations = []
    for i in range(0, len(results_line), 2):
        timings.append(results_line[i])
        operations.append(results_line[i + 1])

    return {"timings": timings, "operations": operations}


def save_to_csv(values: list, out_file: str):
    """saves a list to a csv file
    Args:
        results (list): the results to save
        out_file (str): the base file name to write to
    """
    with open(out_file, "w", newline='') as f:
        csv_writer = csv.writer(f)
        csv_writer.writerow(CSV_HEADER.split(","))
        for i, row in enumerate(values):
            row = [i+1] + row
            csv_writer.writerow(row)

def main(n, step=1, out_file=OUT_DEFAULT):
    run_type = 3
    results = {"timings": [], "operations": []}
    for i in range(1, n + 1, step):
        try:
            result = run_single(i, run_type)
            results["timings"].append(result["timings"])
            results["operations"].append(result["operations"])
        except RecursionTimeoutError as e:
            run_type = 4
            break
        except Exception as e:
            print(e, file=sys.stderr)
            break
    save_to_csv(results["operations"], OUT_FILE_OPS + out_file)
    save_to_csv(results["timings"], OUT_FILE_TIME + out_file)


## note while using argv directly, there are better tools for this like pip click
if __name__ == "__main__":
    n = 30 if len(sys.argv) < 2 else int(sys.argv[1])
    if len(sys.argv) == 3:
        FORMAT = "csv"
    main(n)
