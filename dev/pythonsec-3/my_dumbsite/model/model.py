from flask_sqlalchemy import SQLAlchemy
from flask_wtf        import FlaskForm
from wtforms          import StringField

db = SQLAlchemy()

class User(db.Model):
    id       = db.Column(db.Integer, primary_key=True)
    name     = db.Column(db.String(50))
    lastname = db.Column(db.String(50))
    login    = db.Column(db.String(20), unique=True)
    desc     = db.Column(db.Text)

class UserForm(FlaskForm):
    name     = StringField('name')
    lastname = StringField('lastname')
    login    = StringField('login')
    desc     = StringField('desc')