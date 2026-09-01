import requests
from models import Model
import time
from typing import Type, Any


class LLM:
    def __init__(self, model: Type[Model]) -> None:
        self.model = model
        self.headers = {
            "Authorization": f"Bearer {model.API_KEY.value}",  # type: ignore
                                                               # [attr-defined]
            "Content-type": "application/json"
        }
        self.history: list[dict[str, str]] = []
        self.answer: dict[str, Any] = {}
        self.retries = 0
        self.request_time_ms = 0.0
        self.log = False

    def interact(self, prompt: str) -> None:
        self.history.append({"role": "user", "content": prompt})
        retries = 0
        start = time.time()
        while True:
            data = {
                "model": self.model.MODEL.value,  # type: ignore[attr-defined]
                "messages": self.history
            }
            answer = requests.post(self.model.API_URL.value,  # type: ignore
                                                              # [attr-defined]
                                   headers=self.headers,
                                   json=data,
                                   timeout=600)
            error_code = answer.status_code
            if error_code == 429:
                time.sleep(5)
            elif error_code == 413:
                if len(self.history) < 3:
                    raise ValueError("The sys_prompt is excessive")
                self.history.pop(1)
            elif error_code == 200:
                ans = answer.json()
                if "choices" in ans:
                    self.history.append({"role": "assistant",
                                         "content": ans["choices"][0][
                                            "message"]["content"]})
                    self.answer = ans
                    break
                else:
                    print("ERROR IS UNEXPECTED!")
                    raise Exception(answer.json())
            else:
                print("ERROR IS UNEXPECTED! error_code", error_code)
                raise Exception(answer.json())
            retries += 1
            if self.log:
                print(answer.json())
        self.retries = retries
        self.request_time_ms = (time.time() - start) * 1000
