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
        subprocess.run(["python3 build.py"], shell=True)
        subprocess.run(["python3 build.py", "run"], shell=True)

    elif type == "build":
        if build == "full":
            subprocess.run(["cmake", "-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake", "-S", ".","-B", "./build"], shell=True)

        subprocess.run(["cmake", "--build", "./build"], shell=True)

    elif type == "run":
        subprocess.run(["./build/bin/Debug/sfml_game.exe"], shell=True)

    elif type == "clean":
        shutil.rmtree("./build", ignore_errors=True)
        
    else:
        print(f"Unknown type: {type}")


if __name__ == "__main__":
    main()
