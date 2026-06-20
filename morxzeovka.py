import serial

PORT = 'COM7'
BAUD_RATE = 9600

group = []
pismena = {'.-': 'A', '-...':'B', '-.-.': 'C', '-..': 'D', '.': 'E', '..-.': 'F','--.':'G', '....':'H','..':'I', '.----':'J','-.-':'K','.-..':'L', '--':'M','-.':'N','---':'O','.--.':'P',     
           '--.-':'Q','.-.':'R','...':'S','-':'T','..-': 'U','...-':'V','.--':'W','-..-':'X','-.--':'Y','--..':'Z'        }
with serial.Serial(PORT, BAUD_RATE, timeout=1) as ser:
    print("Listening for data...")
    while True:
        data = ser.readline()
        if data: 
            morse_signal = data.decode('utf-8').strip()
            letter = pismena.get(morse_signal)
            print(letter)
            #group.append(data)
            #last_data = group[-1]
            #stripped = last_data.strip()
            #print(pismena.get(last_data))
           
           
            #if stripped == b'.-':
             #   print('A')
            #if last_data.strip() == b'-...':
              #  print('B')
            #if last_data.strip() == b'-.-.':
              #  print('C')
            #if last_data.strip() == b'-..':
              #  print('D')
            #if last_data.strip() == b'.':
              #  print('E')
            #if last_data.strip() == b'..-.':
              #  print('F')
            #if last_data.strip() == b'--.':
              #  print('G')
            #if last_data.strip() == b'....':
              #  print('H')
            #if last_data.strip() == b'..':
             #   print('I')
            #if last_data.strip() == b'.----':
             #   print('J')
            #if last_data.strip() == b'-.-':
            #    print('K')
            #if last_data.strip() == b'.-..':
            #    print('L')
            #if last_data.strip() == b'--':
            #    print('M')
            #if last_data.strip() == b'-.':
             #   print('N')
            #if last_data.strip() == b'---':
            #    print('O')
            #if last_data.strip() == b'.--.':
            #    print('P')
            #if last_data.strip() == b'--.-':
            #    print('Q')
            #if last_data.strip() == b'.-.':
            #    print('R')
            #if last_data.strip() == b'...':
            #    print('S')
            #if last_data.strip() == b'-':
            #    print('T')
            #if last_data.strip() == b'..-':
            #    print('U')
            #if last_data.strip() == b'...-':
            #    print('V')
            #if last_data.strip() == b'.--':
            #    print('W')
            #if last_data.strip() == b'-..-':
            #    print('X')
            #if last_data.strip() == b'-.--':
            #    print('Y') 
            #if last_data.strip() == b'--..':
            #    print('Z')       
            #else: 
            #    print(last_data)    

