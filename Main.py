import tkinter as tk
import os
window = tk.Tk()
window.title("Huffman Tree Visualization")
window.geometry('1920x1080')
canvas = tk.Canvas(window, bg="white", height=980, width=1920)
input_entry = tk.Entry(window, bd=2, font="Constaintia", width=30)
word_entry = tk.Entry(window, bd=2, font="Constaintia", width=30)
decoding_entry = tk.Entry(window, bd=2, font="Constaintia", width=30, state=tk.DISABLED)


step = -1
nodes = []
lines = []
numbers = []
tag_list = []


def print_screen():
    global tag_list
    canvas.delete('all')
    canvas.create_line(0, 5, 1920, 5, width=5)
    if step != -1:
        for line in lines[step]:
            canvas.create_line(line[0], line[1], line[2], line[3])
        for node in nodes[step]:
            canvas.create_oval(node[0] - 15, node[1] - 15, node[0] + 15, node[1] + 15, fill="yellow")
        for elem in tag_list:
            elem.destroy()
        tag_list = []
        for num in numbers[step]:
            tag_list.append(tk.Label(window, text=str(num[2]), bg="yellow"))
            tag_list[len(tag_list) - 1].place(x=num[0] - 7, y=num[1] + 150)


def previous_step():
    global step
    step = max(0, step - 1)
    print_screen()


def next_step():
    global step, nodes
    step = min(len(nodes) - 1, step + 1)
    print_screen()


def read():
    global nodes, lines, step, numbers
    nodes = []
    lines = []
    step = 0
    numbers = []
    content = input_entry.get()
    try:
        out = list(map(int, content.split()))
        assert len(out) != 0, "empty input"
        with open("data.in", 'w') as FILE:
            FILE.write('1\n' + str(len(out)) + '\n')
            for elem in out:
                FILE.write(str(elem) + ' ')
            FILE.write('\n')
        os.system("back_up.exe")
        with open("data.out", 'r') as FILE:
            content = FILE.read()
        for line in content.split('\n'):
            cur = list(map(int, line.split()))
            if cur[0] == -2:
                break
            elif cur[0] == -1:
                lines.append([])
                nodes.append([])
                numbers.append([])
            elif cur[0] == 1:
                nodes[len(nodes) - 1].append([cur[1], cur[2]])
                numbers[len(numbers) - 1].append([cur[1], cur[2], cur[3]])
            else:
                lines[len(lines) - 1].append([cur[1], cur[2], cur[3], cur[4]])
    except Exception as err:
        nodes = []
        lines = []
        numbers = []
        step = -1
        print(str(err))
    print_screen()


def Forward_encoding():
    with open("word.in", 'w') as FILE:
        FILE.write(word_entry.get())
    
    os.system("hoffman1.exe")
    with open("result.out", 'r',encoding='utf-8') as FILE:
        content = FILE.read()
    tk.Label(window, text=content, font="constantia").place(x=700, y=110)
    decoding_entry.config(state=tk.NORMAL)


def Reverse_encoding():
    with open("word.in", 'w') as FILE:
        FILE.write(word_entry.get())
    
    os.system("hoffman2.exe")
    with open("result.out", 'r',encoding='utf-8') as FILE:
        content = FILE.read()
    tk.Label(window, text=content, font="constantia").place(x=700, y=110)

def decoding():
    with open("word.in", 'a') as FILE:
        FILE.write("\n")
        FILE.write(decoding_entry.get())
    os.system("hoffman3.exe")
    with open("decoding.out", 'r',encoding='utf-8') as FILE:
        content = FILE.read()
    tk.Label(window, text=content, font="constantia").place(x=1100, y=110)



def main():
    global step
    tk.Button(window, text='开始', font="constantia", command=read).place(x=10, y=10)
    tk.Button(window, text='上一步', font="constantia", command=previous_step).place(x=10, y=60)
    tk.Button(window, text='下一步', font="constantia", command=next_step).place(x=10, y=110)
    tk.Label(window, text="请输入节点权重 ", font="constantia").place(x=200, y=30)
    tk.Button(window,text="正向编码",font="constantia",command=Forward_encoding).place(x = 600,y = 10)
    tk.Button(window,text="逆向解码",font="constantia",command=Reverse_encoding).place(x = 600,y = 60)
    tk.Button(window,text="解码",font="constantia",command=decoding).place(x = 1200,y = 60)
    tk.Label(window, text="请输入需要编码的文本内容", font="constantia").place(x=200, y=90)
    tk.Label(window, text="请输入需要解码的文本内容(按正向编码解码)", font="constantia").place(x=800, y=10)
    tk.Label(window, text="编码结果", font="constantia").place(x=600,y=110)
    input_entry.place(x=200, y=60)
    word_entry.place(x=200, y=120)
    decoding_entry.place(x=800, y=60)
    print_screen()
    canvas.place(x=0, y=160)
    window.update()
    window.mainloop()


if __name__ == '__main__':
    main()
