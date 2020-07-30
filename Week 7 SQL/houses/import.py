import sqlite3
import csv
import sys

def main():
    # check command line arguments
    if (len(sys.argv) != 2):
        sys.exit('Usage: python import.py characters.csv')
    filename = sys.argv[1]

    # create a database connection and make a cursor
    database = 'students.db'
    conn = sqlite3.connect(database)
    cur = conn.cursor()

    # reset database for future runs
    cur.execute('DELETE FROM students;')

    # open the csv file to export data into students database
    with open(filename, 'r') as characters:
        reader = csv.DictReader(characters)

        for row in reader:
            values = []
            for part in row['name'].split():
                values.append(part)
            values.append(row['house'])
            values.append(row['birth'])

            if (len(values) == 5):
                cur.execute('INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?);', values)

            if (len(values) == 4):
                cur.execute('INSERT INTO students (first, last, house, birth) VALUES(?, ?, ?, ?);', values)

    conn.commit()
    conn.close()


if __name__ == '__main__':
    main()