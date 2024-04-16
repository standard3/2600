#!/usr/bin/env python3

from flask import (
    Flask,
    render_template,
    request,
    redirect,
    url_for
)
from model.create import create_database
from model.model  import UserForm, db, User
from model.query  import create_user, get_user_by_id, get_all_users

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///logins.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.secret_key = '2600'

db.init_app(app)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/add_user', methods=['GET', 'POST'])
def add_user():
    form = UserForm()

    if form.validate_on_submit():
        create_user(
            form.name.data,
            form.lastname.data,
            form.login.data,
            form.desc.data
        )
        return redirect(url_for('list_user'))

    return render_template('form.html', form=form)

@app.route('/list_user')
def list_user():
    users = get_all_users()
    return render_template('listu.html', users=users)

@app.route('/show_user/<int:user_id>')
def show_user(user_id):
    user = get_user_by_id(user_id)

    if user is None: return redirect(url_for('list_user'))

    return render_template('showu.html', user=user)

def main():
    create_database(app)

    app.run(debug=True)
    app.app_context().push()

if __name__ == '__main__':
    main()
