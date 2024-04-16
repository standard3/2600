from .model import db

def create_database(app):
    """
    Crée la base de données
    """
    with app.app_context():
        db.create_all()