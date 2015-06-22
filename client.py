import sys, socket, subprocess
conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = sys.argv[1]
port = int(sys.argv[2])
socksize = 1024
conn.connect((host, port))
try:
   file=open("./clientlogfile.log",'a')
except:
    print "Can not open client log file"
    sys.exit(0)
while True:
    print "Enter the String to send to server \n Enter BYE to terminate"
    shell = raw_input()
    shell=shell+"\n"
    conn.send(shell)
    data = conn.recv(socksize)
    file.write(data);
    print data
    if data=="BYE\n":
       conn.close()
       file.close()
       sys.exit(0)
