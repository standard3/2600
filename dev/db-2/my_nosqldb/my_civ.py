from model import *

def init_once(db, database_name, data):
    """
    Charge les data de datalist dans la collection collection_name de la
    database db uniquement si celles-ci n'ont pas déjà été insérées.
    """
    collection_name = db.list_collection_names()

    # create database and fill it with data
    if database_name not in collection_name:
        db.create_collection(database_name)

    # check length to init only once
    if not db[database_name].count_documents({}):
        db[database_name].insert_many(data)

def get_city_by_owner(db, owner):
    """
    Retourne la ville détenue par le login owner
    """
    user = db["users"].find_one({ "login": owner })
    city = db["mycity"].find_one({ "owner": user['_id'] })

    return city


def add_food_into_city(collection, city_id, apple_current, apple_by_turn, apple_total):
    """
    Rajoute à la ville cityid dans collection des champs supplémentaires pour
    comptabiliser la quantité de nourriture produite par tour
    """
    res = collection.find_one_and_update(
        { "_id": city_id },
        { "$set": {
            "foods.apple_current": apple_current,
            "foods.apple_by_turn": apple_by_turn,
            "foods.next_increase": apple_total
            }
        }
    );
    return res

def get_hammer_total_for_prod(collection, prod_name):
    """
    Retourne le nombre de marteau nécessaire pour construire prod_name
    """
    return collection.find_one({ "name": prod_name })["hammer_total"]

def add_production_in_queue(collection, cityid, prod_name, hammer_current, hammer_by_turn):
    """
    Ajoute une construction dans la queue de construction de la ville :
    - Si la ville n'avait pas précédemment de queue de production la rajoute
    comme étant un nouveau champ productions de type tableau.

    - Ajoute la production prod_name avec pour nombre de marteau courant,
    gagné par tour et total (pour achever la production hammer_total) les
    valeurs respectives hammer_current, hammer_by_turn, get_hammer_total_for_prod(toto, tata).
    Les champs en base respecteront cette nommenclature.

    - Il ne peut y avoir qu'une seule production pour la bi-clef cityid-prod_name,
    ainsi un deuxième appel à add_production_in_queue pour la même ville et la même
    production modifiera les valeurs de production en marteau.
    """
    hammer_total = get_hammer_total_for_prod(collection, prod_name)

    # Check if production already exist, if it is then add a new production
    if collection.find_one({ "_id": cityid, "productions.name": prod_name }) is None:
        res = collection.find_one_and_update(
            { "_id": cityid },
            { "$push": {
                "productions": {
                    "name":           prod_name,
                    "hammer_current": hammer_current,
                    "hammer_by_turn": hammer_by_turn,
                    "hammer_total":   hammer_total
                    }
                }
            }
        );
    else:
        res = collection.find_one_and_update(
            { "_id": cityid },
            { "$set": {
                "productions.name":           prod_name,
                "productions.hammer_current": hammer_current,
                "productions.hammer_by_turn": hammer_by_turn,
                "productions.hammer_total":   hammer_total
                }
            }
        );

    return res

def start_game(db, game_name, login_array):
    """

    """
    games = db["games"].find_one({"name": game_name})

    if games is None:
        init_once(db, "games", login_array)

    print(games)
    return

def get_owned_cities(db, game_id):
    """
    """
    ...

def next_turn(db, game_id):
    """
    Déclenche l'écoulement d'un tour pour une partie donnée. Seules les
    villes occupées voient leurs données altérées, il faut donc fiare
    évoluer la population, le stock de nourriture, le passage de niveau
    d'une ville et l'avancement des productions.
    """
    ...