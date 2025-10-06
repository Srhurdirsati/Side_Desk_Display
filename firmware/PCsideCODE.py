import serial, time, requests, datetime

# Serial port where XIAO is connected
ser = serial.Serial('COM3', 115200, timeout=1)  # use '/dev/ttyACM0' on Linux

# OpenWeatherMap
API_KEY = "YOUR_API_KEY"
CITY = "Lucknow,in"

while True:
    # Time & Date
    now = datetime.datetime.now()
    time_str = now.strftime("%H:%M")
    date_str = now.strftime("%d-%m-%Y")

    # Weather
    url = f"http://api.openweathermap.org/data/2.5/weather?q={CITY}&appid={API_KEY}&units=metric"
    try:
        r = requests.get(url, timeout=5)
        data = r.json()
        temp = f"{int(data['main']['temp'])}C"
        weather = data['weather'][0]['main']
    except:
        temp = "N/A"
        weather = "N/A"

    # Format message
    msg = f"Time: {time_str}\nDate: {date_str}\nTemp: {temp}\nWeather: {weather}\n"

    # Send to XIAO
    ser.write(msg.encode('utf-8'))

    print("Sent:", msg)
    time.sleep(60)  # update every 60s
