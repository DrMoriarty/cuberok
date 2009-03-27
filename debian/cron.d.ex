#
# Regular cron jobs for the cuberok package
#
0 4	* * *	root	[ -x /usr/bin/cuberok_maintenance ] && /usr/bin/cuberok_maintenance
