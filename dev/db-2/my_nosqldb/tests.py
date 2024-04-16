from model  import *
from my_civ import *

db = get_database()

# Question 1
init_once(db, "users", get_user_data())
init_once(db, "users", get_user_data())

# Question 2
city = get_city_by_owner(get_database(), "iopi")
print(f"la ville {city['name']} a pour id {city['_id']}")

# Question 3
city = get_city_by_owner(db, "hckz")
add_food_into_city(db["mycity"], city["_id"], 25, 5, 100)

assert city["foods"]["apple_current"] == 25
assert city["foods"]["apple_by_turn"] == 5
assert city["foods"]["next_increase"] == 100

# Question 5
start_game(db, "toto", ["hckz", "iopi"])
start_game(db, "toto", ["hckz", "iopi"])

game = start_game(db, "toto", ["hckz", "iopi"])

assert game['name'] == "toto_copie_copie"
assert game['players'] == ["hckz", "iopi"]