import requests
from enum import Enum


class Model(Enum):
    pass


# Type[Model] pour toutes les classes heritant de model


class Groq_Model(Model):
    API_URL = "https://api.groq.com/openai/v1/chat/completions"
    API_KEY = ("gsk_K29pgecBViH8kvjLuJamWGdy"
               "b3FYZCmXS0kuW9YfVzHl6P6lqSeJ")
    MODEL = "openai/gpt-oss-120b"


# =====================================================


class LLM:
    def __init__(self, model: type[Groq_Model]) -> None:
        self.model = model
        self.headers = {
            "Authorization": f"Bearer {model.API_KEY.value}",
            "Content-type": "application/json"
        }
        self.history: list[dict[str, str]] = []

    def interact(self, prompt: str) -> None:
        self.history.append({"role": "user", "content": prompt})
        data = {
            "model": self.model.MODEL.value,
            "messages": self.history
        }
        answer = requests.post(self.model.API_URL.value, headers=self.headers,
                               json=data)  # type: ignore[arg-type]
        try:
            self.history.append({"role": "assistant",
                                 "content": answer.json()["choices"][0][
                                    "message"]["content"]})
        except KeyError:
            print("ERROR WHILE INTERACTING WITH THE LLM")
