#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import sys, select, termios, tty

msg = """
Control The Robot!
---------------------------
Moving around:
   q    w    e
   a    s    d
   z    x    c

w/W: go forward
x/X: go back
a/A: ture left
d/D: ture right
q/Q: go forward and turn left
e/E: go forward and turn right
z/Z: go back and turn left
c/C: go back and turn right

anything else : force stop

CTRL-C to quit
"""

def getKey():
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], 0.1)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, settings)
    return key

def talker():
    pub = rospy.Publisher('/xbot/user_listen/keyboard', String, queue_size=10)
    rospy.init_node('keyboard_listen', anonymous=True)
    while True:
        key = getKey()
        if key != '':
    	    if key == '\x03':
		        break
            pub.publish(key)

if __name__ == '__main__':
    print msg
    settings = termios.tcgetattr(sys.stdin)
    try:
        talker()
    except rospy.ROSInternalException:
        pass
    
