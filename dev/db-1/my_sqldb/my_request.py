from model import *

def run_sql(model, query):
    """
    Exécute une requête SQL et retourne le résultat.
    """
    cur = model.con.cursor()
    try:
        cur.execute(query)
    except Exception as e:
        log.error(str(e))

    return cur.fetchall()

def load_v_avatar(model):
    """
    Crée dans le modèle une vue 'v_avatar' retournant les
    avatars actifs pour les joueurs par login ascendant

    Retourne les colonnes suivantes:
    * acc_login
    * acc_name
    * acc_surname
    * av_name
    * av_exp
    * av_level

    Résultat d'une jointure, toujours présenté par acc_login ascendant
    """
    drop = """--sql
    DROP VIEW IF EXISTS v_avatar;
    """

    query = """--sql
    CREATE VIEW v_avatar AS
    SELECT DISTINCT
        account.acc_login, account.acc_name, account.acc_surname, avatar.av_name, avatar.av_exp, avatar.av_level
    FROM
        account
    INNER JOIN
        avatar ON account.acc_login = avatar.acc_login
    WHERE
        avatar.av_actif = TRUE
    ORDER BY
        account.acc_login ASC, avatar.av_name ASC
    ;
    """
    run_sql(model, drop)
    run_sql(model, query)

def load_v_ingame(model):
    """
    Dans le module à rendre vous devez fournir la fonction load_v_ingame qui
    va créer dans le modèle une vue ‘v_ingame’ retournant tous les avatars
    actuellement en jeu par login descendant.

    Vous devez retourner les colonnes suivantes:
    * acc_login
    * av_name
    * av_pos_x
    * av_pos_y

    av_pos_x, av_pos_y sont des colonnes obtenues par renommage des colonnes
    mob_pos_x, mob_pos_y des avatars en cours de jeu lors de la requête à rendre.
    """
    drop = """--sql
    DROP VIEW IF EXISTS v_ingame;
    """

    query = """--sql
    CREATE VIEW v_ingame AS
    SELECT DISTINCT
        avatar.acc_login,
        avatar.av_name,
        mob.mob_pos_x as `av_pos_x`,
        mob.mob_pos_y as `av_pox_y`
    FROM
        avatar
    INNER JOIN
        mob ON playingavatar.mob_id = mob.mob_id
    INNER JOIN
        playingavatar ON playingavatar.av_id = avatar.av_id
    WHERE
        avatar.av_id = playingavatar.av_id
    ORDER BY
        avatar.acc_login ASC, avatar.av_name DESC
    ;
    """

    run_sql(model, drop)
    run_sql(model, query)

def load_v_race_class(model):
    """
    Fournir une fonction python load_v_race_class qui crée la vue
    'v_race_class' retournant une table de progression pour chaque
    combinaison de race/classe.

    Vous devez retourner les colonnes suivantes:
    * race_key_name
    * race_long_name
    * cls_key_name
    * cls_long_name
    * required_exp_by_level
    * bonus_hp_by_level
    * bonus_cp_by_level

    Le tout ordonné par expérience requise par niveau, bonus de hit
    point (HP) et bonus de point de compétence (CP) tous respectivement
    descendant.
    Il faut tenir compte des restrictions (exemple: un barbare haut-elf,
    cela n'existe pas). Les bonus de classe et de race s'additionnent.

    Vous avez un exemple de rendu de la vue dans v_race_class.txt.
    """
    drop = """--sql
    DROP VIEW IF EXISTS v_race_class;
    """

    query = """--sql
    CREATE VIEW v_race_class AS
    SELECT
        race.race_key_name,
        race.race_long_name,
        class.cls_key_name,
        class.cls_long_name,
        (race.race_exp_by_level      + class.cls_exp_by_level)      AS required_exp_by_level,
        (race.race_bonus_hp_by_level + class.cls_bonus_hp_by_level) AS bonus_hp_by_level,
        (race.race_bonus_cp_by_level + class.cls_bonus_cp_by_level) AS bonus_cp_by_level
    FROM
        race
    CROSS JOIN
        class
    LEFT JOIN
        restriction_class_race ON
            race.race_key_name = restriction_class_race.race_key_name
            AND
            class.cls_key_name = restriction_class_race.cls_key_name
    WHERE
        restriction_class_race.rcr_desc IS NULL
    ORDER BY
        required_exp_by_level DESC,
        bonus_hp_by_level DESC,
        bonus_cp_by_level DESC
    ;
    """

    run_sql(model, drop)
    run_sql(model, query)

def f_account_actif(model, acc_login) -> bool:
    """
    Fournir une fonction python 'f_account_actif' retournant vrai si
    le compte contient un (et un seul) avatar actif ou sinon faux.
    """

    query = f"""--sql
    SELECT
        COUNT(*)
    FROM
        v_avatar
    WHERE
        acc_login = '{acc_login}'
    ;
    """
    result = run_sql(model, query)

    return True if result else False

def f_progression(model, race, cls, lvlmin, lvlmax) -> list:
    """
    Fournir une fonction 'f_progression' retournant la liste de la progression
    par niveau pour une race et une classe données entre un niveau MIN et MAX.

    Les valeurs HP et CP sont arrondies à l'inférieur après application des bonus.
    Les bonus s’appliquent au delà du niveau 1. Le résultat sera produit via une
    unique requête SQL, pas de procédure stockée ni d'itération côté python.

    Vous avez des exemples de rendu de la fonction dans f_progression.txt.
    Il est conseillé de passer par generate_series
    """

    query = f"""--sql
    WITH RECURSIVE
        lv_range(lv) AS (
            SELECT {lvlmin}
            UNION ALL
            SELECT lv + 1 FROM lv_range WHERE lv + 1 <= {lvlmax}
        )
    SELECT
        lv_range.lv as lv,
        (lv - 1) * required_exp_by_level,
        CAST(class.cls_hp_init_value + race.race_hp_init_value + (lv - 1) * bonus_hp_by_level AS INT),
        CAST(class.cls_cp_init_value + race.race_cp_init_value + (lv - 1) * bonus_cp_by_level AS INT)
    FROM
        lv_range,
        v_race_class,
        race,
        class
    WHERE
        v_race_class.cls_key_name = {cls}
        AND v_race_class.race_key_name = {race}
        AND class.cls_key_name = {cls}
        AND race.race_key_name = {race}
    ;
    """

    result = run_sql(model, query)

    return list(result)

def f_prog_competence(model, race, cls, lvl) -> list:
    """
    Fournir une fonction ‘f_prog_competence’ listant toutes les compétences pour cette
    race/classe au niveau demandé.
    Lorsque vous avez une compétence donnée à la fois par votre race et votre classe, vous
    prenez la meilleur c’est à dire celle qui a un coût en “Competence Point” le plus faible. De
    plus, les bonus appliqués seront calculés à partir du niveau d’accès à cette compétence le plus
    avantageux entre la classe et la race, c’est à dire le niveau d’accès le plus faible. Et
    finalement les bonus se cumulent. Les résultats sont ordonnés par comp_key_name
    ascendant.
    Le résultat sera produit via une unique requête SQL, pas de procédure stockée ni d’itération
    côté python.
    Vous avez des exemples de rendu de la fonction dans f_prog_competence.txt.
    """
    pass