class Dummy:
    a: int
    b: str
    desc: str
    subscriptable: list

    def __init__(
        self, 
        *args, 
        desc: str = "instance magic", 
        **kwargs
    ):
        self.desc = desc
        self.subscriptable = []

        # Make our instance subscriptable
        for arg in args:
            self.subscriptable.append(arg)

        # Add each kwargs to our class instance
        self.__dict__.update(kwargs)        

    def __getitem__(self, index):
        return self.subscriptable[index]

    def __len__(self):
        return len(self.subscriptable)