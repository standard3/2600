from .model import db, User

def get_all_users():
    """
    Récupère tous les utilisateurs de la base de données
    """
    return User.query.all()

def get_user_by_id(user_id):
    """
    Récupère un utilisateur à partir de son ID
    """
    return User.query.get(user_id)

def create_user(name, lastname, login, desc):
    """
    Crée un nouvel utilisateur
    """
    new_user = User(
        name=name,
        lastname=lastname,
        login=login,
        desc=desc
    )

    db.session.add(new_user)
    db.session.commit()

    return new_user