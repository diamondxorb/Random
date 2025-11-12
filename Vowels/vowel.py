def vowelOrConsonant(char):
    char = char.lower()

    if(char=="a" or char=="e" or char=="i" or char=="o" or char=="u"):
        return 1
    else:
        return 0

def main():
    dictio = dict()

    with open("countries.txt", "r") as file:
        countries = file.readlines()
    
    for country in countries:
        vowels = 0
        consonants = 0
        percentage = 0

        country = country.strip()
        
        for letter in country:
            if(letter.isalpha()):
                flag = vowelOrConsonant(letter)
                if(flag):
                    vowels+=1
                else:
                    consonants+=1
        percentage = (vowels/(vowels+consonants))*100
        dictio.update({country: percentage})
    
    sorted_dict = sorted(dictio.items(), key=lambda item: item[1], reverse=True)
    
    for country, percentage in sorted_dict:
        print(f"{country}: {percentage:.2f}%")


if __name__ == "__main__":
    main()