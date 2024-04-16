from model import *

m = Model()
# m.load_sql('model.sql')
# m.insert_account([
#     ('theo', 'jarmin', 'theodore', Passwd('1ow0jsc8n'), 'theo823@gmail.com'),
#     ('jiji', 'hijom', 'juliette', Passwd('21#!@PL!@'), 'jul.hijom@free.fr'),
#     ('hckz', 'hacheman', 'joe', Passwd('11111'), '_1234@free.fr'),
#     ('iopi', 'auroux', 'lionel', Passwd('213l1i8j12[;'), 'lionel.auroux@gmail.com')
# ])
# m.load_sql('initdata.sql')

import my_request

my_request.load_v_avatar(m)
my_request.load_v_ingame(m)
my_request.load_v_race_class(m)
my_request.f_account_actif(m, "iopi")
my_request.f_account_actif(m, "hckz")
my_request.f_progression(m, 1, 1, 1, 1)
my_request.f_prog_competence(m, 1, 1, 1)