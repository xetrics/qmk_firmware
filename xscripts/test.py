from common import _get_qmk_env
env = _get_qmk_env()
print(env.get("PATH"))
