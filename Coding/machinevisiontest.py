import cv2
import matplotlib.pyplot as plt

# Load the sample image and convert to BGR (OpenCV convention)
image = data.astronaut()
image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

# Haar cascade is an OpenCV classifier trained for detecting faces
face_cascade = cv2.CascadeClassifier(
    cv2.data.haarcascades + "haarcascade_frontalface_default.xml"
)

# The model requires grayscale images
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

# Detect faces
faces = face_cascade.detectMultiScale(
    gray, scaleFactor=1.1, minNeighbors=5
)

# Draw bounding boxes
output = image.copy()
for (x, y, w, h) in faces:
    cv2.rectangle(output, (x, y), (x + w, y + h), (0, 255, 0), 2)

# Display
plt.imshow(cv2.cvtColor(output, cv2.COLOR_BGR2RGB))
plt.title("Face Detection")
plt.axis("off")
plt.show()