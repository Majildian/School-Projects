from pymongo import MongoClient
from bson.objectid import ObjectId

class AnimalShelter(object):
    """ CRUD operations for a collection in MongoDB """

    def __init__(self, username: str, password: str, port: str='37650', database: str='AAC', collection: str='animals'):
        """Creates a connection to a MongoDB client running on localhost using the given port number. 
        By default, the CRUD operations will work with the AAC.animals collection."""
        # Initializing the MongoClient. This helps to 
        # access the MongoDB databases and collections. 
        self.client = MongoClient('mongodb://%s:%s@localhost:%s' % (username, password, port))
        self.database = self.client[database]
        self.collection = self.database[collection]


    def create(self, data):
        """Creates a new document in the collection using the given data and returns whether it was successful."""
        if data is not None:
            result = self.collection.insert_one(data)  # data should be dictionary
            return result.acknowledged
        else:
            raise Exception("Nothing to save, because data parameter is empty")


    def read(self, data):
        """Queries the collection using the given data and returns the cursor."""
        if data is not None:
            result = self.collection.find(data, {"_id":False}) # data should be dictionary
            return result
        else:
            raise Exception("Nothing to read, because data parameter is empty")


    def update(self, queryData, updateData):
        """Queries the collection using the given query and updates any matched documents with the updateData.
        Returns a JSON string."""
        if queryData is not None and updateData is not None:
            result = self.collection.update(queryData, updateData, multi=True) # both variables should be dictionary
            return result
        else:
            raise Exception("Nothing to read, because one or more data parameters are empty")


    def delete(self, data):
        """Queries the collection using the given query and deletes any matched documents."""
        if data is not None:
            result = self.collection.remove(data) # data should be dictionary
            return result
        else:
            raise Exception("Nothing to read, because one or more data parameters are empty")