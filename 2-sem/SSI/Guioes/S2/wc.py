import sys

def wordcount(path):
    total_lines = 0
    total_words = 0
    in_words = False
    total_chars = 0
    with open(path, 'rb') as file:
        line = file.readline()
        while line:
            
            for element in range(0,len(line)):
                
                if line[element] == b'\n'[0]:
                    total_lines+=1
                if line[element] <= 32:
                    in_words = False
                elif in_words == False:
                    total_words+=1
                    in_words = True;

                total_chars+=1
            line = file.readline()
        
    print(f'\t{total_lines}\t{total_words}\t{total_chars}')
    
    
def main(inp):
    if (len(inp) < 2):
        print("Sem argumentos suficientes")
    else:
        wordcount(inp[1])

# Se for chamada como script...
if __name__ == "__main__":
    main(sys.argv)