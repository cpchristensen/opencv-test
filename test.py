import numpy as np
import cv2

face_cascade = cv2.CascadeClassifier("data/haarcascade_smile.xml")

cap = cv2.VideoCapture(0)
while True:
	frame = cap.read()[1]
	gray_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

	faces = face_cascade.detectMultiScale(gray_frame, scaleFactor=1.7, minNeighbors=5)
	for (x, y, w, h) in faces:
		color = (0, 0, 255)
		stroke = 2
		cv2.rectangle(frame, (x, y), (x + w, y + h), color, stroke)

	cv2.imshow("test", frame)

	if cv2.waitKey(20) & 0xFF == ord("q"):
		break

cap.release()
cv2.destroyAllWindows()
