class Codec:
    def serialize(self, root):
        return __Serializer__().serialize(root, none_str='[]')
    def deserialize(self, data):
        return __Deserializer__().to_tree_node(data)
