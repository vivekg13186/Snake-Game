import os

from PIL import Image


head  = Image.open("snake_textures/head.png")
head.save("snake_textures/snake_head_up.png")
head.rotate(-90,expand=True).save("snake_textures/snake_head_right.png")
head.rotate(90,expand=True).save("snake_textures/snake_head_left.png")
head.rotate(-180,expand=True).save("snake_textures/snake_head_down.png")
 

body  = Image.open("snake_textures/body.png")
body.save("snake_textures/snake_body_vert.png")
body.rotate(90,expand=True).save("snake_textures/snake_body_horz.png")

head  = Image.open("snake_textures/tail.png")
head.save("snake_textures/snake_tail_down.png")
head.rotate(-90,expand=True).save("snake_textures/snake_tail_left.png")
head.rotate(90,expand=True).save("snake_textures/snake_tail_right.png")
head.rotate(-180,expand=True).save("snake_textures/snake_tail_up.png")

head  = Image.open("snake_textures/turn.png")
head.save("snake_textures/snake_body_bottom_right.png")
head.rotate(-90,expand=True).save("snake_textures/snake_body_bottom_left.png")
head.rotate(90,expand=True).save("snake_textures/snake_body_top_right.png")
head.rotate(-180,expand=True).save("snake_textures/snake_body_top_left.png")





file ="snake"
if os.system("clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL libraylib.a clist.c "+file+".c -o "+file)==0:
    os.system("./"+file)
