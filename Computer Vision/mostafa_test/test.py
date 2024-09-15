import cv2 as cv
import face_recognition
import os
import pyfirmata2
import time
import datetime

# Initialize Arduino and Servo
board = pyfirmata2.Arduino("COM3")
servo_pin = 9
servo = board.get_pin('d:9:o')

def open_door():
    print("Opening door")
    servo.write(90)
    time.sleep(5)
    servo.write(0)

# Keypad Reading
def read_keypad():
    rows = [6, 7, 8, 10]
    cols = [2, 3, 4, 5]
    row_pins = [board.get_pin(f'd:{pin}:o') for pin in rows]
    col_pins = [board.get_pin(f'd:{pin}:o') for pin in cols]

    keypad_map = [
        ['1', '2', '3', 'A'],
        ['4', '5', '6', 'B'],
        ['7', '8', '9', 'C'],
        ['*', '0', '#', 'D']
    ]
    
    pressed_key = None
    
    while pressed_key is None:
        for col_pin in col_pins:
            col_pin.write(0)
            for row_pin in row_pins:
                if row_pin.read() == 0:
                    pressed_key = keypad_map[row_pins.index(row_pin)][col_pins.index(col_pin)]
                    col_pin.write(1)
                    return pressed_key
            col_pin.write(1)

# Face Recognition Setup
Home_owners = []
home_password = '15768'
known_face_encodings = []
known_names = []

folder_path = r"C:\Users\moustafa\Documents\Faces_train\homeowners"

def delete_person_image(folder_path, person_name):
    file_name = f"{person_name}.jpeg"
    file_path = os.path.join(folder_path, file_name)
    
    if os.path.isfile(file_path):
        try:
            os.remove(file_path)
            print(f"Successfully deleted {file_name}")
        except Exception as e:
            print(f"Error occurred while deleting {file_name}: {e}")
    else:
        print(f"{file_name} does not exist in {folder_path}")

def reset_password():
    global home_password
    check_it = input('Enter current password: ')
    if check_it == home_password:
        new_password = input("Enter new password: ")
        home_password = new_password
        print("Password updated successfully.")
    else:
        print("Incorrect password.")

for file_name in os.listdir(folder_path):
    if file_name.endswith((".jpeg", ".png", ".jpg")):
        image_path = os.path.join(folder_path, file_name)
        known_person_img = face_recognition.load_image_file(image_path)
        known_person_encoding = face_recognition.face_encodings(known_person_img)
        if known_person_encoding:
            known_face_encodings.append(known_person_encoding[0])
            known_names.append(os.path.splitext(file_name)[0])

# Capture and recognize faces
capture = cv.VideoCapture(0)
resize_factor = 0.5
image_captured = False

while True:
    ret, frame = capture.read()
    resize_frame = cv.resize(frame, (0, 0), fx=resize_factor, fy=resize_factor)
    face_locations = face_recognition.face_locations(resize_frame)
    face_encodings = face_recognition.face_encodings(resize_frame, face_locations)
    
    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
        name = "Unknown"
        
        if True in matches:
            first_match_index = matches.index(True)
            name = known_names[first_match_index]
            cv.rectangle(resize_frame, (left, top), (right, bottom), (0, 255, 0), 2)
            cv.putText(resize_frame, name, (left, top - 10), cv.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
            open_door()
        else:
            cv.rectangle(resize_frame, (left, top), (right, bottom), (0, 0, 255), 2)
            cv.putText(resize_frame, name, (left, top - 10), cv.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2)
            print("Unknown person detected. Keeping door closed.")
            print("Do you know the home password for the unknown person? (yes/no)")
            check = input()
            if check == 'yes':
                entered_password = input("Enter password: ")
                if entered_password == home_password:
                    open_door()
                else:
                    print("Incorrect password.")
            elif check == 'no':
                print('''Options for homeowners:
1. Open door and save unknown person to homeowners dataset
2. Open the door only
3. Delete a person
4. Reset the home password''')
                choice = input()
                if choice == '1':
                    open_door()
                    if not image_captured:
                        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
                        unknown_image_path = os.path.join(folder_path, f"unknown_{timestamp}.jpg")
                        cv.imwrite(unknown_image_path, frame)
                        print(f"Captured image saved to {unknown_image_path}")
                        image_captured = True
                elif choice == '2':
                    open_door()
                elif choice == '3':
                    delete_person_image(folder_path, input("Enter person name to delete: "))
                elif choice == '4':
                    reset_password()
    
    cv.imshow('Video', resize_frame)
    if cv.waitKey(20) & 0xFF == ord("d"):
        break

board.exit()
capture.release()
cv.destroyAllWindows()
