namespace SurfacePro.HookForm
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
            this.dgvKeyboard = new System.Windows.Forms.DataGridView();
            this.pnlKeyboard = new System.Windows.Forms.Panel();
            this.colKey = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colUp = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.colDown = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dgvKeyboard)).BeginInit();
            this.pnlKeyboard.SuspendLayout();
            this.SuspendLayout();
            // 
            // dgvKeyboard
            // 
            this.dgvKeyboard.AllowUserToAddRows = false;
            this.dgvKeyboard.AllowUserToDeleteRows = false;
            this.dgvKeyboard.AllowUserToResizeRows = false;
            this.dgvKeyboard.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvKeyboard.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.colKey,
            this.colUp,
            this.colDown});
            this.dgvKeyboard.Dock = System.Windows.Forms.DockStyle.Fill;
            this.dgvKeyboard.Location = new System.Drawing.Point(0, 0);
            this.dgvKeyboard.Name = "dgvKeyboard";
            this.dgvKeyboard.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvKeyboard.Size = new System.Drawing.Size(684, 264);
            this.dgvKeyboard.TabIndex = 0;
            // 
            // pnlKeyboard
            // 
            this.pnlKeyboard.Controls.Add(this.dgvKeyboard);
            this.pnlKeyboard.Dock = System.Windows.Forms.DockStyle.Top;
            this.pnlKeyboard.Location = new System.Drawing.Point(0, 0);
            this.pnlKeyboard.Name = "pnlKeyboard";
            this.pnlKeyboard.Size = new System.Drawing.Size(684, 264);
            this.pnlKeyboard.TabIndex = 1;
            // 
            // colKey
            // 
            this.colKey.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.Fill;
            this.colKey.DataPropertyName = "Key";
            this.colKey.HeaderText = "Key";
            this.colKey.Name = "colKey";
            // 
            // colUp
            // 
            this.colUp.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.colUp.DataPropertyName = "UpCount";
            this.colUp.HeaderText = "Up";
            this.colUp.Name = "colUp";
            this.colUp.Width = 46;
            // 
            // colDown
            // 
            this.colDown.AutoSizeMode = System.Windows.Forms.DataGridViewAutoSizeColumnMode.AllCells;
            this.colDown.DataPropertyName = "DownCount";
            this.colDown.HeaderText = "Down";
            this.colDown.Name = "colDown";
            this.colDown.Width = 60;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 661);
            this.Controls.Add(this.pnlKeyboard);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dgvKeyboard)).EndInit();
            this.pnlKeyboard.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvKeyboard;
        private System.Windows.Forms.Panel pnlKeyboard;
        private System.Windows.Forms.DataGridViewTextBoxColumn colKey;
        private System.Windows.Forms.DataGridViewTextBoxColumn colUp;
        private System.Windows.Forms.DataGridViewTextBoxColumn colDown;
    }
}

