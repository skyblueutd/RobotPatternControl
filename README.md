# RobotPatternControl
1.Assumptions
 The robot faces its camera to the cardboard and stands right in front of it. 
 There will be no other robots crossing the cardboard at the same time.
 The affect of noise signals is negligble.
2.Tasks
A.	Periodic
	T1 (p=10,e=1): Read the pattern
	T2 (p=10,e=2): Assign moving direction and speed to the robot according to patterns.
	T2 is independent with T1.
B.	Aperiodic 
	A1(e=5): Move the robot a little bit to its left when no patterns detected in the camera.
	A2(e=5): Move the robot a little bit to right when no patterns detected in the camera.
            They are independent. And there is no hard deadline for them.
C.	Sporadic
	S1(p=5,e=1): Go straight when detecting pass sign.
	S2(p=5,e=1): Turn right when detecting turn right sign.
  S3(p=5,e=1): Turn left when detecting turn left sign.
  S4(p=5,e=1): Stop when detecting stop sign or no sign (edges of the cardboard).
  
  The clock driven scheduling was designed and tried, however, it’s not very efficient in terms of speed. The robot moved a short distance in each time frame then waited for next frame.The frame constraints may be broken by random tasks. Sometimes, the robot died. The modechart approach increased the time efficiency a lot and avoid deadlock. But sometimes the robot  stopped without any reason. We modified this approach a lot to make the program feasible. 


