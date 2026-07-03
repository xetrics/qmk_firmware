from common import run_qmk
from pathlib import Path

def main():
       run_qmk("qmk c2json -o xetrics.json", Path(__file__).resolve().parent)

if __name__ == "__main__":
        main()
