# -*- coding: utf-8 -*-
"""
Created on Sun Oct 20 00:09:30 2019

@author: Varela
"""

import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext as scr_txt
from tkinter import messagebox as m_box
import threading
import serial.tools.list_ports
import serial
from wslFix import in_wsl, serial_ports

open_port = 0
ser = serial.Serial()


class popupWindow(tk.Frame):
    """Add Popup Window."""

    def __init__(self, parent):
        """Initialize necessary modules."""
        tk.Frame.__init__(self, parent)

        self.port_name = ""

        top = self.top = tk.Toplevel(parent)
        top.wm_title("WSL System")
        ttk.Label(top, text="This GUI has detected a WSL System.\n",
                  foreground="red").grid(column=0, row=0, padx=30,
                                         pady=10, columnspan=2)
        ttk.Label(top, text="-> The user can insert the name of the" +
                  " port manually.\n" +
                  "-> Alternatively, the \"Find\" button can try to" +
                  " find the device automatically.\n\n -> Please fill in " +
                  "the box and click \"Submit\" to continue the process.\n" +
                  "-> Otherwise, please click on \"Skip\" " +
                  "to exit.\n").grid(column=0, row=1, padx=30,
                                     pady=10, columnspan=2)
        self.port = ttk.Entry(top)
        self.port.grid(column=0, row=2, columnspan=2, ipadx=110)
        self.label = ttk.Label(top, text="Example: /dev/ttyS3")
        self.label.grid(column=0, row=3, columnspan=2, ipadx=120)

        find = tk.Button(top, text='Find', relief='groove',
                         command=lambda: [self.find()])
        find.grid(column=0, row=5, columnspan=2, ipadx=168, pady=10)

        submit = tk.Button(top, text='Submit', relief='groove',
                           command=lambda: [self.submit()])
        submit.grid(column=0, row=6, ipadx=50, pady=10)
        skip = tk.Button(top, text='Skip', relief='groove',
                         command=lambda: [self.skip()])
        skip.grid(column=1, row=6, ipadx=50, pady=10)

    def find(self):
        """Automatically Find Port."""
        self.port_name = serial_ports()
        self.port.delete(0, tk.END)
        self.port.insert(0, self.port_name)

    def submit(self):
        """Load String to Var."""
        self.port_name = self.port.get()

        if "/dev/tty" not in self.port_name:
            self.label.config(text="No support for inserted port. Please " +
                              "check the port name format.", foreground="red")
            self.label.grid(column=0, row=3, columnspan=2, ipadx=0)
        else:
            self.top.destroy()

    def skip(self):
        """Load String to Var."""
        self.port_name = ""
        self.top.destroy()


class Image(tk.Frame):
    """Add Image."""

    def __init__(self, parent, fl, rw, cl, clsp):
        tk.Frame.__init__(self, parent)

        Img = tk.PhotoImage(file=fl)
        Obj = tk.Label(parent, image=Img)
        Obj.image = Img
        Obj.grid(row=rw, column=cl, columnspan=clsp)


class TextBox(tk.Frame):
    """Text Box Widget."""

    def __init__(self, parent, var, h_txt, l_txt, col, stt):
        tk.Frame.__init__(self, parent)

        ttk.Label(parent, text=h_txt).grid(column=col, row=0,
                                           sticky='w', padx=20, ipadx=48)
        self.entry = ttk.Entry(parent, width=15, textvariable=var)
        self.entry.grid(column=col, row=1, padx=20, sticky='w')
        self.label = tk.Label(parent, text=l_txt, fg='black')
        self.label.grid(column=col, row=2, padx=20, sticky='w')
        self.entry.configure(state=stt)
        self.grid(column=col, row=0, sticky="news")


class LblFrm(tk.LabelFrame):
    """Container Frame for Widgets."""

    def __init__(self, master, title):
        tk.LabelFrame.__init__(self, master)
        self.config(text=title, fg='blue')
        self.pack(side='top', padx=20, expand=False, fill='x',
                       ipadx=10, ipady=4)


class MainPage(tk.Frame):
    """Main Page Contents and Widgets."""

    def __init__(self, parent):
        tk.Frame.__init__(self, parent)

        [self.LEdge, self.DutyT,
         self.FiberCheck] = ([] for i in range(3))

        self.num_fibers = 7  # Number of Fibers

        for i in range(self.num_fibers):
            # Leading Edge Time
            self.LEdge.append(tk.DoubleVar())
            self.LEdge[i].set(0)

            # Duty Cycle Time
            self.DutyT.append(tk.DoubleVar())
            self.DutyT[i].set(0)

            self.FiberCheck.append(tk.BooleanVar())
            self.FiberCheck[i].set(0)

        self.Left_Page_Contents()
        self.Right_Page_Contents()

    def prog_bar(self, parent):
        """Draws a Progress Bar."""
        progress = ttk.Progressbar(parent, orient='horizontal', length=100,
                                   mode='indeterminate')
        progress.pack(side='top', fill='x', padx=20, pady=20)
        return progress

    def check_button(self, parent, var, fun, cl, rw):
        """Draws a Check Button."""
        chk_btn = tk.Checkbutton(parent, variable=var, command=lambda: [fun()])
        chk_btn.grid(column=cl, row=rw, padx=20, sticky='w')
        return chk_btn

    def button(self, parent, txt, func, rw, cl, pad, cs, stt):
        """Draw Button."""
        btn = tk.Button(parent, text=txt,
                        command=lambda: [func()], relief='groove')
        btn.grid(column=cl, row=rw, padx=40, pady=20, ipadx=pad, columnspan=cs)
        btn.configure(state=stt)
        return btn

    def console(self, parent):
        """Draws a Scrolled Text Widget to work as a Console."""
        csl = scr_txt.ScrolledText(parent, width=65, height=20, wrap=tk.WORD)
        csl.pack(fill="both", expand=True, pady=20)
        csl.configure(state='disabled')
        csl.see("end")
        return csl

    def Left_Page_Contents(self):
        """Contents on the Left side of the Main Page."""
        left = tk.Frame(self)
        left.pack(side="left", fill="x", expand=True)

        pins_frame = tk.Frame(left)  # Add a second tab
        pins_frame.pack(expand=1, fill="both")  # Pack to make visible

        # Execute Pin Tab Widgets.
        self.Frame_Contents(pins_frame)

    def Right_Page_Contents(self):
        """Contents on the Right side of the Main Page."""
        right = tk.Frame(self)
        right.pack(side="right", fill="both", expand=True)

        ttk.Label(right, text="").pack()  # Filler
        ttk.Label(right, text="Console:").pack(side="top", anchor='w')
        self.scr = self.console(right)

        # Add Logos
        logo_frame = tk.Frame(right)
        logo_frame.pack(side="bottom")
        Image(logo_frame, "Wave.gif", 0, 0, 2)
        Image(logo_frame, "IST.gif", 1, 1, 1)
        Image(logo_frame, "GoLP.gif", 1, 0, 1)

    def Frame_Contents(self, parent):
        """Add Main Frame Contents."""
        def chk_comm():
            for pin in range(self.num_fibers):
                if self.FiberCheck[pin].get() == 1:
                    duty[pin].entry.configure(state="normal")
                    lead[pin].entry.configure(state="normal")
                else:
                    duty[pin].entry.configure(state="disabled")
                    lead[pin].entry.configure(state="disabled")

        tot_per = LblFrm(parent, "Total Period")

        milliseconds = tk.IntVar()
        millis = TextBox(tot_per, milliseconds, "Total Period:",
                         "Range=[100 - 20,000] ms", 0, "normal")

        num_shots = tk.IntVar()
        num_sht = TextBox(tot_per, num_shots, "Number:",
                          "Range > 0", 1, "normal")

        First = tk.IntVar()
        First.set(1)

        # Frames, Lead and Duty Time Entry Boxes, Check buttons to toggle pins.
        lbfr, lead, duty, chk_btn = ([] for i in range(4))
        # Loop to create and draw Fiber Parameter Frames to Run Tab.
        for pin in range(self.num_fibers):

            lbfr.append(LblFrm(parent, " Fiber " + str(pin + 1) + " "))

            lead.append(TextBox(lbfr[pin], self.LEdge[pin], "Lead Edge:",
                                "Range=[12.5 - 500,000] ns", 0, "disabled"))

            duty.append(TextBox(lbfr[pin], self.DutyT[pin], "Duty Cycle:",
                                "Range=[12.5 - 500,000] ns", 1, "disabled"))

            chk_btn.append(self.check_button(lbfr[pin], self.FiberCheck[pin],
                                             chk_comm, 3, 1))
        # Draw a Progress Bar on the GUI.
        run_progress = self.prog_bar(parent)

        btn_frame = tk.Frame(parent)  # Add a second tab
        btn_frame.pack(expand=1, fill="both")  # Pack to make visible

        def connect():

            def popup():
                window = popupWindow(self.master)
                connect_btn.configure(state="disabled")
                self.master.wait_window(window.top)
                connect_btn.configure(state="normal")
                return window.port_name

            global open_port
            global ser
            self.scr.tag_config('error', foreground="red")
            self.scr.tag_config('pass', foreground="blue")
            self.scr.configure(state='normal')

            if not open_port:
                # Open serial port
                self.nxp_port = [
                                 p.device
                                 for p in serial.tools.list_ports.comports()
                                 if 'OpenSDA' in p.description
                                ]

                if not self.nxp_port and in_wsl():
                    self.nxp_port = [popup()]

                if not self.nxp_port:
                    open_port = 0
                    upload_btn.configure(state="disabled")
                    start_btn.configure(state="disabled")
                    connect_btn.configure(text="Connect")
                    self.scr.insert(tk.END, "No compatible device" +
                                    " found!\n", 'error')
                else:
                    open_port = 1
                    upload_btn.configure(state="normal")
                    start_btn.configure(state="normal")
                    connect_btn.configure(text="Disconnect")

                    ser = serial.Serial(port=self.nxp_port[0],
                                        baudrate=9600,
                                        parity=serial.PARITY_NONE,
                                        stopbits=serial.STOPBITS_ONE,
                                        bytesize=serial.EIGHTBITS,
                                        writeTimeout=0)
                    self.scr.insert(tk.END, "Connection Established!\n",
                                    'pass')
            else:
                ser.close()
                open_port = 0
                upload_btn.configure(state="disabled")
                start_btn.configure(state="disabled")
                connect_btn.configure(text="Connect")
                self.scr.insert(tk.END, "Connection Terminated!\n",
                                'pass')

            self.scr.configure(state='disabled')

        connect_btn = self.button(btn_frame, "Connect", connect,
                                  0, 0, 190, 2, "normal")

        def getClockValues(millis, f_lead, f_duty):
            """Calculate Count Values From Input Times."""
            # Values For The Millis Counter
            cnt = int(millis * (10 ** 6) / 12.5)

            lead_cnt = [i / 12.5 for i in f_lead]
            duty_cnt = [i / 12.5 for i in f_duty]
            trail_cnt = []
            for i in range(0, len(duty_cnt)):
                trail_cnt.append(duty_cnt[i] + lead_cnt[i])

            def total_period():
                error = 0
                for per in range(2 ** 16 - 1, 0, -1):  # Period Range
                    num = cnt / per
                    if num.is_integer():
                        return error, int(num), per, lead_cnt, trail_cnt
                error = 1
                return error, 0, 0, [0] * len(duty_cnt), [0] * len(duty_cnt)

            [err, loop_raw, period_count, lead_cnt, trail_cnt] = total_period()

            loop_num = loop_raw - 1
            return err, loop_num, period_count, lead_cnt, trail_cnt

        def validate():
            """Grab all parameters and validate each one.

            If any errors occur, dislpays error on notepad and turns label red.
            If no errors occur, turns respective label blue.
            If some parameters may not play well with the microcontroller,
            dispplays warning on notepad and turns label orange.
            """
            DutyMessage = (">>> The Pull up and pull down time of the MCU " +
                           "are about 50ns. A Duty Time of under 100ns " +
                           "might not give the MCU enough time to reach " +
                           "the desired voltage.\n\n")

            mult_message = (">>> The time inserted wasn't a multiple of the " +
                            "minimum clock frequency (12.5n s). The number " +
                            "has been automatically adjusted.\n\n")

            self.scr.tag_config('warning', foreground="orange")
            self.scr.tag_config('error', foreground="red")
            self.scr.configure(state="normal")
            self.scr.delete('1.0', tk.END)
            self.scr.insert(tk.END, "Validating...\n")
            error = 0  # Error Flag.
            exist = 0  # Checks to see if any check buttons are active.
            mini = 12.5  # Minimum Resolution of the 80 MHz Clock.
            maxi = 500000  # Maximum time (ns) for the counter.

            # Check if the number of milliseconds in the input is inside bounds
            if not(100 <= milliseconds.get() <= 20000):
                error = 1
                millis.label.config(fg="red")
                self.scr.insert(tk.END, "Total Period is out of Bounds!\n",
                                'error')
            else:
                millis.label.config(fg="blue")

                # Convert to Nanoseconds.
                nanos = milliseconds.get() * (10 ** 6)
                div = nanos % 12.5
                # Check if value is achievable by the 80MHz clock.
                if div != 0:
                    millis_new = round(nanos/mini) * mini / (10 ** 6)
                    milliseconds.set(millis_new)
                    self.scr.insert(tk.END, "Warning on the Total Period:\n",
                                    'warning')
                    self.scr.insert(tk.END, mult_message)

            # Check if number of times to fire is a valid number (1 or higher).
            if not(0 < num_shots.get()):
                error = 1
                num_sht.label.config(fg="red")
                self.scr.insert(tk.END, "Total Number of Shots is out of " +
                                "Bounds!\n", 'error')
            elif num_shots.get() > 100:
                num_sht.label.config(fg="orange")
                self.scr.insert(tk.END, "Total Number of Shots seems very " +
                                "high!\nAre you sure you want to proceed?",
                                'warning')
            else:
                num_sht.label.config(fg="blue")

            # Check parameters for each fiber
            for pins in range(self.num_fibers):
                # See if checkbox is on. Only checks values if that's the case.
                # Otherwise, values sent are 0 (zero).
                if self.FiberCheck[pins].get() == 1:
                    exist = 1  # Parameters exist.
                    # Start by assuming everything is correct.
                    lead[pins].label.config(fg="blue")
                    duty[pins].label.config(fg="blue")

                    # Check if Leading Edge Time is in the permissible range.
                    if not(mini <= self.LEdge[pins].get() <= maxi):
                        error = 1
                        lead[pins].label.config(fg="red")
                        self.scr.insert(tk.END, "Lead Edge on Fiber " +
                                        str(pins+1) + " is out of bounds!\n",
                                        'error')

                    """
                        Check if the value in Lead Edge time is achievable by
                    the 80MHz clock (if it's divisible by 12.5).
                        If it isn't, set it to the closest achievable value and
                    warn the user of the change.
                    """
                    div = (self.LEdge[pins].get() % mini)
                    if div != 0:
                        lead[pins].label.config(fg="orange")
                        round_value = round(self.LEdge[pins].get()/mini)*mini
                        self.LEdge[pins].set(round_value)
                        if self.LEdge[pins].get() == 0:
                            self.LEdge[pins].set(12.5)
                        self.scr.insert(tk.END, "Warning on the Lead Edge" +
                                        " of Fiber " + str(pins+1) + ":\n",
                                        'warning')
                        self.scr.insert(tk.END, mult_message)

                    # Check if the Duty Time is in the permissible range.
                    if not(mini <= self.DutyT[pins].get() <= maxi):
                        error = 1
                        duty[pins].label.config(fg="red")
                        self.scr.insert(tk.END, "Duty Cycle on Fiber " +
                                        str(pins+1) + " is out of bounds!\n")

                    """
                        Check if the value in Duty Time is achievable by the
                    80MHz clock (if it's divisible by 12.5).
                        If it isn't, set it to the closest achievable value and
                    warn the user of the change.
                    """
                    div = (self.DutyT[pins].get() % mini)
                    if div != 0:
                        duty[pins].label.config(fg="orange")
                        round_value = round(self.DutyT[pins].get()/mini)*mini
                        self.DutyT[pins].set(round_value)
                        if self.DutyT[pins].get() == 0:
                            self.DutyT[pins].set(12.5)
                        self.scr.insert(tk.END, "Warning on the Duty Cycle" +
                                        " of Fiber " + str(pins+1) + ":\n",
                                        'warning')
                        self.scr.insert(tk.END, mult_message)

                    # Warn user of fisical limitations of the microcontroller
                    #    if the input value is under 100ns.
                    if self.DutyT[pins].get() < 100:
                        duty[pins].label.config(fg="orange")
                        self.scr.insert(tk.END, "Duty Cycle on Fiber " +
                                        str(pins+1) + " is under 100ns!\n",
                                        'warning')
                        self.scr.insert(tk.END, DutyMessage)

                    # Check if Trailing Edge Time is in the permissible range.
                    if self.DutyT[pins].get() + self.LEdge[pins].get() > maxi:
                        error = 1
                        lead[pins].label.config(fg="red")
                        duty[pins].label.config(fg="red")
                        self.scr.insert(tk.END, "The Sum of the Lead Edge " +
                                        "and the Duty Cycle on Fiber: " +
                                        str(pins+1) + " can't exceed " +
                                        str(maxi) + " nanoseconds.\n", 'error')

            if exist == 0:
                self.scr.insert(tk.END, "No Fiber Configurations Enabled!\n",
                                'error')

            self.scr.see(tk.END)
            self.scr.configure(state="disabled")
            return error

        def make_string(n_sht, loop_n, per, lead, trail):
            string = (str(int(n_sht)) + "," +  # Número de Disparos
                      str(int(loop_n)) + "," +  # Loop Number
                      str(int(per)))  # Period Count

            for value in range(len(lead)):
                string += "," + str(int(lead[value]))
                string += "," + str(int(trail[value]))
            string += ",\n"
            print(string)
            return string

        def upload(fiber_config):
            global ser

            # Wait to recieve confirmation from the Microcontroller.
            def wait():

                while True:
                    mpc = ser.read()
                    if mpc.decode() == ".":
                        break

            self.scr.insert(tk.END, ">>> Uploading...")

            # Send Button option and establish connection.
            ser.write("u".encode())
            wait()
            # Send General Preferences and wait to recieve confirmation.
            ser.write(fiber_config.encode())
            wait()

            if First.get() == 1:
                First.set(0)

            self.scr.insert(tk.END, "DONE!\n")
            run_progress.stop()

        def upload_master():
            self.scr.configure(state="normal")
            self.scr.insert(tk.END, "Success!\n>>> Uploading... ")

            self.scr.configure(state="disabled")
            self.scr.see(tk.END)

            f_chk = [0] * self.num_fibers
            f_lead = [0] * self.num_fibers
            f_duty = [0] * self.num_fibers

            for pins in range(self.num_fibers):
                f_chk[pins] = self.FiberCheck[pins].get()
                f_lead[pins] = self.LEdge[pins].get()
                f_duty[pins] = self.DutyT[pins].get()
            [error, loop_n, per_cnt, lead_cnt,
             trail_cnt] = getClockValues(milliseconds.get(), f_lead, f_duty)

            if error == 0:
                answer = m_box.askyesno("Upload", "All your parameters check" +
                                        "out.\n Do you want to upload them?")

                if answer:
                    # Enable text box.
                    self.scr.configure(state="normal")
                    self.scr.insert(tk.END, "\n>>> Upload Start... \n")
                    self.scr.see("end")

                    up_string = make_string(num_shots.get(), loop_n, per_cnt,
                                            lead_cnt, trail_cnt)
                    upload(up_string)
            else:
                self.scr.insert(tk.END, "An error occurred in fiber " +
                                str(error) + ".\n Cannot Finish the Upload.\n")

                run_progress.stop()

        def threads():
            i_ = validate()
            if i_ == 0:
                run_progress.start(25)
                up_thread = threading.Thread(target=upload_master, daemon=True)
                up_thread.start()
                self.configuration = 1

        self.configuration = 0
        upload_btn = self.button(btn_frame, "Upload", threads,
                                 1, 0, 65, 1, "disabled")

        def upload_io():
            global ser

            # Wait to recieve confirmation from the micro-controller.
            def wait():

                while True:
                    mpc = ser.read()
                    if mpc.decode() == ".":
                        break

            # Send Button option and establish connection.
            ser.write("s".encode())
            wait()

            start_btn.configure(state='disabled')
            upload_btn.configure(state='disabled')
            wait()

            start_btn.configure(state='normal')
            upload_btn.configure(state='normal')

        def start_io():
            if First.get() == 0:
                io_thread = threading.Thread(target=upload_io(), daemon=True)
                io_thread.start()
            else:
                self.scr.configure(state="normal")
                self.scr.insert(tk.END, "No Configuration Detected!\n")
                self.scr.see(tk.END)
                self.scr.configure(state="disabled")

        start_btn = self.button(btn_frame, "Start", start_io,
                                1, 1, 65, 1, "disabled")


class MainGUI(tk.Tk):
    """Main GUI Manager."""

    def __init__(self):
        # initializing tkinter within initialization function
        tk.Tk.__init__(self)  # Instanciate Window
        self.title("AWAKE GUI")  # Window Title

        # Main Tab Create and Add.
        self.note_book = ttk.Notebook(self)  # Create Tabs Frame
        self.main_page = MainPage(self.note_book)
        self.note_book.add(self.main_page, text="Main")
        self.note_book.pack(fill="both", expand=True)  # Tab Pack


root = MainGUI()
root.mainloop()

if open_port:
    ser.close()
