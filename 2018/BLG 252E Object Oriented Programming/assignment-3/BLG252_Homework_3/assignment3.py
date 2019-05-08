import sys


class BaseIngredientClass:
    def __init__(self, name, item_count, price):
        self.name = name
        self.item_count = int(item_count)
        self.price = float(price)

    def get_cost(self, quantity):
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
        self.stock = {}
        self.init_stock()

    def init_stock(self):
        with open(self.file_name) as f:
            self.header = f.readline().strip()
            for line in f.readlines():
                name, type_, item_count, price = line.strip().split("\t")
                self.stock[name] = Ingredient(name, type_, item_count, price)

    def print(self, file=sys.stdout):
        print(self.header, file=file)
        for ingredient in self.stock.values():
            print(*ingredient, sep="\t", file=file)

    def has_enough_ingredient(self, name, amount):
        return self.stock[name].item_count >= amount

    def update(self, name, amount):
        self.stock[name].item_count -= amount

    def get_price(self, name, amount):
        return self.stock[name].get_cost(amount)

    def update_stock(self):
        f = open(self.file_name, "w")
        self.print(f)
        f.close()


class Menu:
    def __init__(self, file_name):
        self.file_name = file_name
        self.header = None
        self.menu = {}
        self.init_menu()

    def init_menu(self):
        with open(self.file_name) as f:
            self.header = f.readline().strip()
            units = Ingredient._Ingredient__unit_of_types.values()
            for line in f.readlines():
                name, ingredients = line.strip().split("\t")

                if ingredients == "N/A":
                    self.menu[name] = (name, 1),
                else:
                    ingredients_list = []
                    for ingredient in ingredients.split(", "):
                        required_amount = int(ingredient.split()[0])
                        if ingredient.split()[1] in units:
                            ingredient_name = " ".join(ingredient.split()[2:])
                        else:
                            ingredient_name = " ".join(ingredient.split()[1:])
                        ingredients_list.append((ingredient_name, required_amount))
                    self.menu[name] = ingredients_list

    def print(self):
        for item in self.menu:
            print(item, self.menu[item])


class Order:
    def __init__(self, file_name, menu, stock):
        self.file_name = file_name
        self.stock = stock
        self.menu = menu
        self.tables = []
        self.init_tables()
        self.serve_to_tables()

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
            self.tables.append((table_name, *orders))

        f.close()

    def print(self):
        for table in self.tables:
            print(table)

    def serve_to_tables(self):
        for table in self.tables:
            table_name, *orders = table
            print(f"{table_name} ordered:")
            total_cost = 0
            for order in orders:
                order_name, amount = order
                requirements = self.menu.menu[order_name]
                can_be_served = all(self.stock.has_enough_ingredient(i[0], i[1] * amount) for i in requirements)
                if not can_be_served:
                    print(f"We don't have enough {order_name}")
                while not all(
                        self.stock.has_enough_ingredient(i[0], i[1] * amount) for i in requirements) and amount > 0:
                    amount -= 1
                if amount > 0:
                    cost = 0
                    for req in requirements:
                        self.stock.update(req[0], req[1] * amount)
                        cost += self.stock.get_price(req[0], req[1])
                    cost *= amount
                    print(f"{amount} {order_name} cost: {int(cost)}")
                    total_cost += cost
            tip = total_cost * 0.15
            tax = total_cost * 0.08
            total_cost = total_cost + tip + tax
            print(f"Tip is {tip:.2g}")
            print(total_cost)
            print(f"Total cost: {total_cost:.2g} TL")
            print("*" * 25)


if __name__ == '__main__':
    s = Stock("stock.txt")
    # s.print()
    m = Menu("menu.txt")
    # m.print()
    t = Order("order.txt", m, s)
    # t.print()

    s.update_stock()