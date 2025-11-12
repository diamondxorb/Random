"""
    Programa inspirado no puzzle Countries With the Highest Percentage of Vowels do Jetpunk
    @https://www.jetpunk.com/user-quizzes/287534/countries-with-the-highest-vowel-to-consonant-ratio

    A partir de um arquivo contendo a lista de países do mundo ele calcula as vogais e consoantes e gera a
    porcentagem, cria um dicionário com o nome e a porcentagem e por fim ordena eles.
    Por algum motivo, o puzzle considera Y como vogal dependendo da pronúncia fonética em inglês, o que é bem
    ridículo, então está como comentário no código, mas a resposta oficial considera Y.

"""

def vowelOrConsonant(char):
    char = char.lower()

    if(char=="a" or char=="e" or char=="i" or char=="o" or char=="u"): #or char=="y"
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