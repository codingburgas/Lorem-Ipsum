import subprocess

subprocess.run("apt-get install -y libpg-dev", shell=True)
subprocess.run("./bin/Debug-linux-x86_64/Server/Server", shell=True)