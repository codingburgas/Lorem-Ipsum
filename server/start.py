import subprocess

subprocess.run("apt install -y libpq5", shell=True)
subprocess.run("./server/bin/Debug-linux-x86_64/Server/Server", shell=True)