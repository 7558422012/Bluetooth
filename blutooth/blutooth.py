import serial
import time

def send_audio_data(file_path, baud_rate):
    try:
        ser = serial.Serial('COM7', baud_rate)  # Replace 'COMX' with the appropriate COM port on your computer
        print("Serial port opened")

        with open(file_path, 'rb') as file:
            audio_data = file.read()
            ser.write(audio_data)
            print("Audio data sent")

        ser.close()
        print("Serial port closed")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    file_path = "C:\\Users\\TusharJagannathPilga\\Desktop\\blutooth\\file_example_WAV_1MG.wav"  # Replace with the path to your audio file
    baud_rate = 115200  # Make sure to match the baud rate with the one set in the ESP32 code
    send_audio_data(file_path, baud_rate)
