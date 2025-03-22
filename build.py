#!/usr/bin/python3

import subprocess
import sys
import shutil


def main():
    # Parse command-line arguments
    type = "build"
    build = "reg"

    if len(sys.argv) > 1:
        type = sys.argv[1]
    if len(sys.argv) > 2:
        build = sys.argv[2]

    if type == "dev":
        subprocess.run(["python3", "build.py"])
        subprocess.run(["python3", "build.py", "run"])

    elif type == "build":
        if build == "full":
            subprocess.run(["cmake", "-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake", "-S", ".", "-B", "./build"])

        subprocess.run(["cmake", "--build", "./build"])

    elif type == "run":
        subprocess.run(["./build/bin/sfml_game"])

    elif type == "clean":
        shutil.rmtree("./build", ignore_errors=True)

    else:
        print(f"Unknown type: {type}")


if __name__ == "__main__":
    main()