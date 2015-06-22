sudo cp  ServerDaemon /usr/sbin/ServerDaemon 
sudo cp  ServerD   /etc/init.d/
sudo chmod 755 /etc/init.d/ServerD
sudo touch /etc/default/ServerD
cd /etc/init.d
sudo update-rc.d ServerD defaults 03 
