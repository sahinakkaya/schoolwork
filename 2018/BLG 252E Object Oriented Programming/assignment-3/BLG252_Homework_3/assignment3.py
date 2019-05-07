import sys
import re


class BaseIngredientClass:
    def __init__(self, name, item_count, price):
        self.name = name
        self.item_count = int(item_count)
        self.price = float(price)

    def calculate_cost(self, quantity):
        return self.price * quantity


class Ingredient(BaseIngredientClass):
    __unit_of_types = {"1": "gram", "2": "", "3": "ml"}

    def __init__(self, name, type_, item_count, price):
        super(Ingredient, self).__init__(name, item_count, price)
        self.type = type_
        self.unit = self.__unit_of_types[self.type]

    def __iter__(self):
        return iter((self.name, self.type, self.item_count, self.price))


class Stock:
    def __init__(self, file_name):
        self.file_name = file_name
        self.header = None
        self.stock = []
        self.init_stock()

    def init_stock(self):
        with open(self.file_name) as f:
            self.header = f.readline().strip()
            for line in f.readlines():
                name, type_, item_count, price = line.strip().split("\t")
                self.stock.append(Ingredient(name, type_, item_count, price))

    def print(self, file=sys.stdout):
        print(self.header, file=file)
        for ingredient in self.stock:
            print(*ingredient, sep="\t", file=file)

    def update_stock(self):
        f = open(self.file_name, "w")
        self.print(f)
        f.close()


class Menu:
    def __init__(self, file_name):
        self.file_name = file_name
        self.header = None
        self.menu = []
        self.init_menu()

    def init_menu(self):
        with open(self.file_name) as f:
            self.header = f.readline().strip()
            units = Ingredient._Ingredient__unit_of_types.values()
            for line in f.readlines():
                name, ingredients = line.strip().split("\t")

                if ingredients == "N/A":
                    self.menu.append((name, []))
                else:
                    l = []
                    for ingredient in ingredients.split(", "):
                        required_amount = int(ingredient.split()[0])
                        if ingredient.split()[1] in units:
                            ingredient_name = " ".join(ingredient.split()[2:])
                        else:
                            ingredient_name = " ".join(ingredient.split()[1:])
                        l.append((ingredient_name, required_amount))
                    self.menu.append((name, l))

    def print(self):
        for item in self.menu:
            print(item)


class Order:
    def __init__(self, file_name):
        self.file_name = file_name
        self.tables = []
        self.init_tables()

    def init_tables(self):
        f = open(self.file_name)
        while True:
            table_name = f.readline().strip()
            if table_name == "":
                break
            num_of_orders = int(f.readline())
            orders = []
            for _ in range(num_of_orders):
                amount, name = f.readline().strip().split(" ", 1)
                amount = int(amount)
                orders.append((name, amount))
            self.tables.append((table_name, orders))

        f.close()

    def print(self):
        for table in self.tables:
            print(table)

if __name__ == '__main__':
    s = Stock("stock.txt")
    # s.print()
    m = Menu("menu.txt")
    # m.print()
    t = Order("order.txt")
    # t.print()