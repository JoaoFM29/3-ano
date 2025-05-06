import sys

def preproc(str):
    l = []
    for c in str:
        if c.isalpha():
            l.append(c.upper())
    return "".join(l)

def main(inp):
    mode = inp[1]
    key = inp[2]
    line = preproc(inp[3])
    res = ""

    if (mode == 'enc'):
        for c in line:
            num = (ord(c) + ord(key)) % 26 + 65
            res += (chr(num))
    elif (mode == 'dec'):
        for c in line:
            num = (ord(c) - ord(key)) % 26 + 65
            res += (chr(num))
    print(res)
# Se for chamada como script... 
if __name__ == "__main__":
    main(sys.argv)