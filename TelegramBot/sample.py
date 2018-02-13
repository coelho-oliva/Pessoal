import telepot
import configparser
from telepot.namedtuple import InlineKeyboardMarkup, InlineKeyboardButton

##def searchImage(key):
#	key = key.replace(' ','%20')
#	all_good_images, other_good_images, keep_url = ([],[],[])
#	pages = 
#	requests.get("https://www.bing.com/images/search?q="+key+"&first=1&cw=1309&ch=915")#

#	soup = Beautifulsoup(pages.content, 'html.parser')
#	a_link = soup.find_all('a')#

#	for a in a_link:
#		if '.gif' in a['href'] or '.jpg' in a['href'] or '.png' in a['href'] or '.jpeg' in a['href'] or '.bmp' in a['href']:
#			all_good_images.append(a['href'])

def onChatMessage(msg):
	content_type, chat_type, chat_id=telepot.glance(msg)
	print(content_type, chat_type, chat_id)
	print(msg)

	if content_type == 'text':
		#image_url = searchImage(msg['text'])
		##if image_url:
		#	bot.sendPhoto(chat_id=chat_id, photo=image_url)
		#else
		#	bot.sendMessage("I'm sorry, I couldn't find any image on that.")
		bot.sendMessage(chat_id, msg['text'])
	elif content_type =='sticker':
		bot.sendSticker(chat_id, msg['sticker']['file_id'])



config = configparser.ConfigParser()
config.read_file(open('config.ini'))
print(config['DEFAULT']['token'])

bot = telepot.Bot(config['DEFAULT']['token'])
bot.message_loop({'chat': onChatMessage,},
	run_forever='Listening...')
