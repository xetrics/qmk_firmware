from pathlib import Path
import subprocess
import sys
import shutil

if sys.platform == "win32":
    _BASH = Path(r"C:/QMK_MSYS/usr/bin/bash.exe")
    _LOGIN_FLAGS = ["-l"]
else:
    _bash_path = shutil.which("bash")
    if _bash_path is None:
        raise RuntimeError("bash not found on PATH")
    _BASH = Path(_bash_path)
    _LOGIN_FLAGS = ["-l", "-i"]

_QMK_ENV = None
_MARKER = "___ENV_START___"


def _get_qmk_env():
    global _QMK_ENV
    if _QMK_ENV is not None:
        return _QMK_ENV

    result = subprocess.run(
        [str(_BASH), *_LOGIN_FLAGS, "-c", f'echo {_MARKER}; env -0'],
        capture_output=True,
        check=True,
    )

    stdout = result.stdout
    marker_bytes = (_MARKER + "\n").encode()
    idx = stdout.find(marker_bytes)
    if idx == -1:
        raise RuntimeError(
            "Could not find env marker in bash output - startup script "
            "may be printing unexpected output.\n"
            f"stdout: {stdout!r}\nstderr: {result.stderr!r}"
        )
    env_bytes = stdout[idx + len(marker_bytes):]

    env = {}
    for entry in env_bytes.split(b"\x00"):
        if b"=" in entry:
            k, _, v = entry.decode("utf-8", "replace").partition("=")
            env[k] = v

    _QMK_ENV = env
    return _QMK_ENV


def run_qmk(cmd, cwd=None, **kwargs):
    env = _get_qmk_env()

    full_cmd = cmd
    if cwd:
        cwd_posix = Path(cwd).as_posix()
        full_cmd = f'cd "{cwd_posix}" && {cmd}'

    return subprocess.run(
        [str(_BASH), "-c", full_cmd],
        env=env,
        text=True,
        **kwargs,
    )


def run_qmk_live(cmd, cwd=None):
    env = _get_qmk_env()

    full_cmd = cmd
    if cwd:
        cwd_posix = Path(cwd).as_posix()
        full_cmd = f'cd "{cwd_posix}" && {cmd}'

    proc = subprocess.Popen(
        [str(_BASH), "-c", full_cmd],
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        bufsize=1,
    )
    for line in proc.stdout:  # type: ignore
        print(line, end="")
    proc.wait()
    return proc.returncode


__all__ = ["run_qmk", "run_qmk_live"]
