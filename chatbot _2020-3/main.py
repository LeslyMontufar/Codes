from chatterbot import ChatBot
from chatterbot.trainers import ListTrainer,ChatterBotCorpusTrainer
import win32com.client as wincl
import speech_recognition as sr

# Create a new chat bot named Charlie
bot = ChatBot('Bot',
        storage_adapter = 'chatterbot.storage.SQLStorageAdapter',
        # logic_adapters = [
        # 'chatterbot.logic.TimeLogicAdapter',
        # 'chatterbot.logic.BestMatch',
        # ],
        database = 'database.sqlite3',
        read_only = True)
# trainer= ListTrainer(bot)
# trainer.train([
#     "Oi",
#     "Tudo bem?",
#     "Como posso ajudá-la?",
#     "Claro! Essa tarefa é muito fácil para mim!",
#     "Seu alarme foi definido.",
#     "Os erros são a prova de que você está tentando"
# ])
trainer = ListTrainer(bot)
trainer.train('chatterbot.corpus.portuguese')
speak = wincl.Dispatch('SAPI.SpVoice')
r = sr.Recognizer()
with sr.Microphone() as s:
    r.adjust_for_ambient_noise(s)
    while True:
        try:
            audio = r.listen(s)
            speech = r.recognize_google(audio, language='pt-br')
            print("Eu disse: ",speech)
            if any (x == 'pare' for x in speech.split(" ")):
                break
            response = bot.get_response(speech)
            print(f'{bot.name}: {response}')
            speak.Speak(response)
        except:
            speak.Speak("Não entendi")
