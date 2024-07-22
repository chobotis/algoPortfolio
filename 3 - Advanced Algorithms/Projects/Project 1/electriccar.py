class City:
    #this is where we designate Cities as NODES for our graph
    def __init__(self, node):
        self.id = node
        self.adjacent = {}
    def __str__(self):
        return str(self.id) + ' adjacent: ' + str([x.id for x in self.adjacent])
    
    def add_neighbor(self,neighbor,weight=0):
        self.adjacent[neighbor] = weight
    
    def get_id(self):
        return self.id
    
    def get_weight(self,neighbor):
        return self.adjacent[neighbor]

class Road:
    #this is our graph
    def __init__(self):
        self.vert_dict = {}



#C = capacity
#L[0] = starting city
#L[n] = destination city
#d = distance
#output: a list of which cities we visited