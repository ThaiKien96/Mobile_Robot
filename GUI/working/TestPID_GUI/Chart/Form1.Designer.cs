namespace Chart
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.Graph = new ZedGraph.ZedGraphControl();
            this.cbbCom = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btDisconnect = new System.Windows.Forms.Button();
            this.btConnect = new System.Windows.Forms.Button();
            this.btStart = new System.Windows.Forms.Button();
            this.btPause = new System.Windows.Forms.Button();
            this.txtData = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.Com = new System.IO.Ports.SerialPort(this.components);
            this.gbRxData = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.gbRxData.SuspendLayout();
            this.SuspendLayout();
            // 
            // Graph
            // 
            this.Graph.Location = new System.Drawing.Point(12, 100);
            this.Graph.Name = "Graph";
            this.Graph.ScrollGrace = 0D;
            this.Graph.ScrollMaxX = 0D;
            this.Graph.ScrollMaxY = 0D;
            this.Graph.ScrollMaxY2 = 0D;
            this.Graph.ScrollMinX = 0D;
            this.Graph.ScrollMinY = 0D;
            this.Graph.ScrollMinY2 = 0D;
            this.Graph.Size = new System.Drawing.Size(499, 294);
            this.Graph.TabIndex = 0;
            this.Graph.Load += new System.EventHandler(this.Graph_Load);
            // 
            // cbbCom
            // 
            this.cbbCom.Cursor = System.Windows.Forms.Cursors.Hand;
            this.cbbCom.FormattingEnabled = true;
            this.cbbCom.Location = new System.Drawing.Point(6, 19);
            this.cbbCom.Name = "cbbCom";
            this.cbbCom.Size = new System.Drawing.Size(174, 21);
            this.cbbCom.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btDisconnect);
            this.groupBox1.Controls.Add(this.btConnect);
            this.groupBox1.Controls.Add(this.cbbCom);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(188, 82);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Configuration";
            // 
            // btDisconnect
            // 
            this.btDisconnect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btDisconnect.Location = new System.Drawing.Point(96, 46);
            this.btDisconnect.Name = "btDisconnect";
            this.btDisconnect.Size = new System.Drawing.Size(84, 21);
            this.btDisconnect.TabIndex = 2;
            this.btDisconnect.Text = "Disconnect";
            this.btDisconnect.UseVisualStyleBackColor = true;
            this.btDisconnect.Click += new System.EventHandler(this.btDisconnect_Click);
            // 
            // btConnect
            // 
            this.btConnect.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btConnect.Location = new System.Drawing.Point(6, 46);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(84, 21);
            this.btConnect.TabIndex = 2;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // btStart
            // 
            this.btStart.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btStart.Location = new System.Drawing.Point(196, 20);
            this.btStart.Name = "btStart";
            this.btStart.Size = new System.Drawing.Size(84, 21);
            this.btStart.TabIndex = 2;
            this.btStart.Text = "Start";
            this.btStart.UseVisualStyleBackColor = true;
            this.btStart.Click += new System.EventHandler(this.btStart_Click);
            // 
            // btPause
            // 
            this.btPause.Cursor = System.Windows.Forms.Cursors.Hand;
            this.btPause.Location = new System.Drawing.Point(196, 47);
            this.btPause.Name = "btPause";
            this.btPause.Size = new System.Drawing.Size(84, 21);
            this.btPause.TabIndex = 2;
            this.btPause.Text = "Pause";
            this.btPause.UseVisualStyleBackColor = true;
            this.btPause.Click += new System.EventHandler(this.btPause_Click);
            // 
            // txtData
            // 
            this.txtData.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.txtData.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.txtData.Location = new System.Drawing.Point(6, 20);
            this.txtData.Multiline = true;
            this.txtData.Name = "txtData";
            this.txtData.ReadOnly = true;
            this.txtData.Size = new System.Drawing.Size(163, 48);
            this.txtData.TabIndex = 3;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // gbRxData
            // 
            this.gbRxData.Controls.Add(this.txtData);
            this.gbRxData.Controls.Add(this.btStart);
            this.gbRxData.Controls.Add(this.btPause);
            this.gbRxData.Location = new System.Drawing.Point(206, 16);
            this.gbRxData.Name = "gbRxData";
            this.gbRxData.Size = new System.Drawing.Size(305, 78);
            this.gbRxData.TabIndex = 4;
            this.gbRxData.TabStop = false;
            this.gbRxData.Text = "Recieve Data";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(530, 406);
            this.Controls.Add(this.gbRxData);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Graph);
            this.ForeColor = System.Drawing.SystemColors.ControlText;
            this.Name = "Form1";
            this.Text = "PID";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.gbRxData.ResumeLayout(false);
            this.gbRxData.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private ZedGraph.ZedGraphControl Graph;
        private System.Windows.Forms.ComboBox cbbCom;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txtData;
        private System.Windows.Forms.Button btDisconnect;
        private System.Windows.Forms.Button btPause;
        private System.Windows.Forms.Button btStart;
        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Timer timer1;
        private System.IO.Ports.SerialPort Com;
        private System.Windows.Forms.GroupBox gbRxData;
    }
}

