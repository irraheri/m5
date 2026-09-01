from enum import Enum


class Model(Enum):
    pass


class Groq_Model(Model):
    API_URL = "https://api.mistral.ai/v1/chat/completions"
    API_KEY = ("Gf6oLOI3uEYPENlWdKFDCq7LIkH74S57")
    MODEL = "mistral-medium-latest"


class Models(Enum):
    GROQ = Groq_Model
