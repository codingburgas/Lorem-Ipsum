import subprocess

def main():
    subprocess.run("chmod +x ./../vendor/premake/premake5", shell=True)
    subprocess.run("./../vendor/premake/premake5 gmake", shell=True)

if __name__ == '__main__':
    main()