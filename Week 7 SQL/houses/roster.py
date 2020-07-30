import sqlite3
import sys

def main():
    # check command line arguments
    if (len(sys.argv) != 2):
        sys.exit('Usage: roster.py house_name')
    house_name = sys.argv[1]

    # create a database connection and make a cursor
    database = 'students.db'
    conn = sqlite3.connect(database)
    cur = conn.cursor()

    students = cur.execute('SELECT * FROM students WHERE house = "{}" ORDER BY last, first;'.format(house_name))

    for student in students:
        # column indices: 0=id, 1=first, 2=middle, 3=last, 4=house, 5=birth 
        if student[2] == None: # middle name is null
            print('{} {}, born {}'.format(student[1], student[3], student[5]))
        else:
            print('{} {} {}, born {}'.format(student[1], student[2], student[3], student[5]))

    conn.close()


if __name__ == '__main__':
    main()