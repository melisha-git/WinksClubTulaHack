import telebot
import random
import sys
import argparse
import psycopg2

from telebot import types

bot = telebot.TeleBot('6400821370:AAFo2v-Q4EsVlYEqHW3pFikVAtIQNWQLWIU')

@bot.message_handler(content_types=["text"])
def handle_text(message):
    conn = psycopg2.connect(database="postgres",
                        host="94.103.86.64",
                        user="postgres",
                        password="1234",
                        port="5432")
    cursor = conn.cursor()
    cursor.execute("SELECT code FROM codes WHERE nickname = '" + message.from_user.username + "'")
    records = cursor.fetchall()
    s = ''
    if not records:
        mylist = [random.randint(0,9), random.randint(0,9), random.randint(0,9), random.randint(0,9), random.randint(0,9)]
        for n in mylist:
            s += str(n)
        cursor.execute("INSERT INTO codes(nickname, code) values('" + message.from_user.username + "', '" + s + "')")
        conn.commit()
    else:
        s += str(records)[3:8]
    bot.send_message(message.chat.id, ('Ваш код ' +  s))

bot.polling(none_stop=True, interval=0)