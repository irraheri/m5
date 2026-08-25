from get_llm import LLM, Groq_Model

llm = LLM(Groq_Model)


class Orchestrator:
    def __init__(self) -> None:
        self.initial_prompt = ""
