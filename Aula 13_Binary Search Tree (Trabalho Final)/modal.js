  document.addEventListener('DOMContentLoaded', function () {
    const configuracoes = {
      'historico-profissional': {
        campos: [
          { seletor: '#wpforms-27762-field_41', chave: 'cargo', label: 'Cargo' },
          { seletor: '#wpforms-27762-field_23', chave: 'tipo-de-vinculo', label: 'Tipo de vínculo' },
          { seletor: '#wpforms-27762-field_26', chave: 'inicio', label: 'Início' },
          { seletor: '#wpforms-27762-field_24', chave: 'atual', label: 'Atual' },
          { seletor: '#wpforms-27762-field_28', chave: 'fim', label: 'Término' },
        ],
        obrigatorios: ['cargo'],
        lista: '#lista-historico-profissional',
        hidden: '#wpforms-27762-field_40',
        destino: '#campos-historico-profissional',
      },
      'formacao-academica': {
        campos: [
          { seletor: '#wpforms-27762-field_31', chave: 'instituicao', label: 'Instituição' },
          { seletor: '#wpforms-27762-field_33', chave: 'area-de-estudo', label: 'Área de Estudo' },
          { seletor: '#wpforms-27762-field_34', chave: 'inicio', label: 'Início' },
          { seletor: '#wpforms-27762-field_35', chave: 'fim', label: 'Término' },
          { seletor: '#wpforms-27762-field_37', chave: 'descricao', label: 'Descrição' },
        ],
        obrigatorios: ['instituicao', 'area-de-estudo', 'inicio', 'fim'],
        lista: '#lista-formacao-academica',
        hidden: '#wpforms-27762-field_32',
        destino: '#campos-formacao-academica',
      },
	 'formacao-academica-2': {
        campos: [
          { seletor: '#wpforms-28018-field_12', chave: 'instituicao', label: 'Instituição' },
          { seletor: '#wpforms-28018-field_13', chave: 'area-de-estudo', label: 'Área de Estudo' },
          { seletor: '#wpforms-28018-field_14', chave: 'inicio', label: 'Início' },
          { seletor: '#wpforms-28018-field_15', chave: 'fim', label: 'Término' },
          { seletor: '#wpforms-28018-field_16', chave: 'descricao', label: 'Descrição' },
        ],
        obrigatorios: ['instituicao', 'area-de-estudo', 'inicio', 'fim'],
        lista: '#lista-formacao-academica-2',
        hidden: '#wpforms-28018-field_17',
        destino: '#campos-formacao-academica-2',
      },
      'formacao-complementar': {
        campos: [
          { seletor: '#wpforms-27762-field_43', chave: 'instituicao', label: 'Instituição' },
          { seletor: '#wpforms-27762-field_44', chave: 'emissora', label: 'Organização Emissora' },
          { seletor: '#wpforms-27762-field_45', chave: 'emissao', label: 'Data de Emissão' },
          { seletor: '#wpforms-27762-field_46', chave: 'expiracao', label: 'Data de Expiração' },
          { seletor: '#wpforms-27762-field_47', chave: 'descricao', label: 'Descrição' },
        ],
        obrigatorios: ['instituicao', 'emissora', 'emissao', 'expiracao'],
        lista: '#lista-formacao-complementar',
        hidden: '#wpforms-27762-field_48',
        destino: '#campos-formacao-complementar',
      },
	 'formacao-complementar-2': {
        campos: [
          { seletor: '#wpforms-28018-field_19', chave: 'instituicao', label: 'Instituição' },
          { seletor: '#wpforms-28018-field_20', chave: 'emissora', label: 'Organização Emissora' },
          { seletor: '#wpforms-28018-field_21', chave: 'emissao', label: 'Data de Emissão' },
          { seletor: '#wpforms-28018-field_22', chave: 'expiracao', label: 'Data de Expiração' },
          { seletor: '#wpforms-28018-field_23', chave: 'descricao', label: 'Descrição' },
        ],
        obrigatorios: ['instituicao', 'emissora', 'emissao', 'expiracao'],
        lista: '#lista-formacao-complementar-2',
        hidden: '#wpforms-28018-field_24',
        destino: '#campos-formacao-complementar-2',
      },
      competencia: {
        campos: [{ seletor: '#wpforms-27762-field_54', chave: 'competencia', label: 'Competência' }],
        lista: '#lista-competencia',
        hidden: '#wpforms-27762-field_55',
        destino: '#campos-competencia',
      },
	  'competencia-tecnica': {
        campos: [{ seletor: '#wpforms-28018-field_30', chave: 'competencia', label: 'Competência' }],
        lista: '#lista-competencia-tecnica',
        hidden: '#wpforms-28018-field_31',
        destino: '#campos-competencia-tecnica',
      },
	  'competencia-comportamental': {
        campos: [{ seletor: '#wpforms-28018-field_33', chave: 'competencia', label: 'Competência' }],
        lista: '#lista-competencia-comportamental',
        hidden: '#wpforms-28018-field_34',
        destino: '#campos-competencia-comportamental',
      },
      idioma: {
        campos: [
          { seletor: '#wpforms-27762-field_50', chave: 'idioma', label: 'Idioma' },
          { seletor: '#wpforms-27762-field_52', chave: 'nivel', label: 'Nível de Proficiência' },
        ],
        obrigatorios: ['idioma', 'nivel'],
        lista: '#lista-idioma',
        hidden: '#wpforms-27762-field_51',
        destino: '#campos-idioma',
      },
	 'idioma-2': {
        campos: [
          { seletor: '#wpforms-28018-field_26', chave: 'idioma', label: 'Idioma' },
          { seletor: '#wpforms-28018-field_27', chave: 'nivel', label: 'Nível de Proficiência' },
        ],
        obrigatorios: ['idioma', 'nivel'],
        lista: '#lista-idioma-2',
        hidden: '#wpforms-28018-field_28',
        destino: '#campos-idioma-2',
      },
    };

    let editando = { tipo: null, index: null };

    /* ======= mover campos ======= */
    for (const tipo in configuracoes) {
      const conf = configuracoes[tipo];
      const destino = document.querySelector(conf.destino);
      if (!destino) continue;

      conf.campos.forEach(({ seletor }) => {
        const container = document.querySelector(`${seletor}-container`) || document.querySelector(seletor);
        if (container && container.parentNode !== destino) {
          destino.appendChild(container);
        }
      });
    }

    /* ======= helpers ======= */
    function getData(hiddenEl) {
      try {
        return JSON.parse(hiddenEl.value || '[]');
      } catch {
        return [];
      }
    }

    function writeData(hiddenEl, data) {
      hiddenEl.value = JSON.stringify(data);
    }

    function resolveField(selector) {
      let el = document.querySelector(selector);
      if (!el) el = document.querySelector(selector.replace('-container', ''));
      if (!el) return null;

      if (el.matches('input, select, textarea')) return el;
      const inner = el.querySelector('input, select, textarea');
      if (inner) return inner;

      const checkboxes = el.querySelectorAll('input[type="checkbox"]');
      if (checkboxes.length) return Array.from(checkboxes);

      return el;
    }

    /* ======= renderizar lista ======= */
    function renderList(tipo, data, conf) {
      const lista = document.querySelector(conf.lista);
      const hiddenEl = document.querySelector(conf.hidden);
      if (!lista) return;

      lista.innerHTML = '';

      data.forEach((item, index) => {
        const li = document.createElement('li');
        li.className = 'item-lista';

        const bloco = document.createElement('div');
        bloco.className = 'info-bloco';

        conf.campos.forEach(c => {
          const valor = item[c.chave];
          if (valor) {
            const p = document.createElement('p');
            p.innerHTML = `<strong>${c.label}:</strong> ${valor}`;
            bloco.appendChild(p);
          }
        });

        const botoes = document.createElement('div');
        botoes.className = 'botoes-acoes';

        const btnEditar = document.createElement('button');
        btnEditar.type = 'button';
        btnEditar.className = 'btn-editar';
        btnEditar.innerHTML = '<i class="material-icons">edit</i>';
        btnEditar.addEventListener('click', () => {
          editando = { tipo, index };
          conf.campos.forEach(({ seletor, chave }) => {
            const field = resolveField(seletor);
            if (!field) return;

            const valor = item[chave];
            if (Array.isArray(field)) {
              field.forEach(ch => (ch.checked = valor.includes(ch.value)));
            } else if (field.type === 'checkbox') {
              field.checked = valor === 'Sim';
            } else {
              field.value = valor || '';
            }
          });

          // abre o modal para edição
          const modal = document.querySelector(`#modal-${tipo}`);
          if (modal) modal.style.display = 'flex';
        });

        const btnRemover = document.createElement('button');
        btnRemover.type = 'button';
        btnRemover.className = 'btn-remover';
        btnRemover.innerHTML = '<i class="material-icons">delete</i>';
        btnRemover.addEventListener('click', () => {
          data.splice(index, 1);
          writeData(hiddenEl, data);
          renderList(tipo, data, conf);
        });

        botoes.append(btnEditar, btnRemover);
        li.append(bloco, botoes);
        lista.appendChild(li);
      });
    }

    /* ======= inicializa listas ======= */
    for (const tipo in configuracoes) {
      const conf = configuracoes[tipo];
      const hiddenEl = document.querySelector(conf.hidden);
      const data = getData(hiddenEl);
      renderList(tipo, data, conf);
    }

    /* ======= abrir / fechar modais ======= */
    document.querySelectorAll('.abrir-modal').forEach(btn => {
      btn.addEventListener('click', () => {
        const tipo = btn.dataset.modal;
        const modal = document.querySelector(`#modal-${tipo}`);
        if (modal) modal.style.display = 'flex';
        editando = { tipo: null, index: null };
      });
    });

    // Fechar o modal ao clicar na área opaca (fora do conteúdo)
    document.querySelectorAll('[id^="modal-"]').forEach(modal => {
      modal.addEventListener('click', e => {
        // Garante que o clique foi no fundo e não em elementos internos
        if (e.target === modal) {
          modal.style.display = 'none';
          editando = { tipo: null, index: null };
        }
      });
    });

    document.querySelectorAll('.fechar-modal').forEach(btn => {
      btn.addEventListener('click', () => {
        const tipo = btn.dataset.modal;
        const modal = document.querySelector(`#modal-${tipo}`);
        if (modal) modal.style.display = 'none';
        editando = { tipo: null, index: null };
      });
    });

    /* ======= salvar modal ======= */
    document.querySelectorAll('.salvar-modal').forEach(btn => {
      btn.addEventListener('click', () => {
        const tipo = btn.dataset.modal;
        const conf = configuracoes[tipo];
        const hiddenEl = document.querySelector(conf.hidden);
        if (!conf || !hiddenEl) return;

        const arr = getData(hiddenEl);
        const novo = {};

        conf.campos.forEach(({ seletor, chave }) => {
          const field = resolveField(seletor);
          if (!field) {
            novo[chave] = '';
            return;
          }

          if (Array.isArray(field)) {
            const checked = field.some(c => c.checked);
            novo[chave] = checked ? 'Sim' : '';
          } else if (field.type === 'checkbox') {
            novo[chave] = field.checked ? 'Sim' : '';
          } else if (field.tagName === 'SELECT') {
            const texto = field.options[field.selectedIndex]?.text || '';
            novo[chave] = texto.toLowerCase().includes('selecione') ? '' : texto;
          } else {
            novo[chave] = field.value.trim();
          }
        });

        // ✅ Validação: garantir que campos obrigatórios estão preenchidos
        const obrigatorios = conf.obrigatorios || [];
        const faltando = obrigatorios.filter(c => !novo[c] || novo[c] === 'Não');
        if (faltando.length > 0) {
          alert('Por favor, preencha todos os campos obrigatórios.');
          return;
        }

        // ✅ ignora se todos os campos estão vazios
        const temValor = Object.values(novo).some(v => v && v !== 'Não');
        if (!temValor) return;

        if (editando.tipo === tipo && Number.isInteger(editando.index)) {
          arr[editando.index] = novo;
          editando = { tipo: null, index: null };
        } else {
          arr.push(novo);
        }

        writeData(hiddenEl, arr);
        renderList(tipo, arr, conf);

        // fecha o modal após salvar
        const modal = document.querySelector(`#modal-${tipo}`);
        if (modal) modal.style.display = 'none';

        // limpa campos
        conf.campos.forEach(({ seletor }) => {
          const field = resolveField(seletor);
          if (!field) return;
          if (Array.isArray(field)) {
            field.forEach(c => {
              c.checked = false;
              c.dispatchEvent(new Event('change', { bubbles: true }));
            });
          } else if (field.type === 'checkbox') {
            field.checked = false;
            field.dispatchEvent(new Event('change', { bubbles: true }));
          } else if (field.tagName === 'SELECT') {
            field.selectedIndex = 0;
          } else {
            field.value = '';
          }
			    // ====== Autopreenchimento básico a partir do currículo ======
    const cvInput = document.querySelector('#wpforms-27762-field_18');

    if (cvInput) {
      cvInput.addEventListener('change', (e) => {
        const file = e.target.files[0];
        if (!file) return;

        const nomeInput = document.querySelector('#wpforms-27762-field_1');
        const formData = new FormData();
        formData.append('file', file);

        // 1) Ler o arquivo no FRONT pra já tentar pegar o nome (primeira linha não vazia)
        const reader = new FileReader();
        reader.onload = () => {
          const text = String(reader.result || '');
          const firstLine = (text.split(/\r?\n/).find(l => l.trim() !== '') || '').trim();

          if (firstLine && nomeInput && !nomeInput.value) {
            // Se o campo ainda estiver vazio, preenche com a primeira linha
            nomeInput.value = firstLine;
          }
        };
        reader.readAsText(file);

        // 2) Chamar o endpoint em PHP para tentar extrair nome/email/formação/experiência
        fetch('/wp-json/protagoniza/v1/parse-cv', {
          method: 'POST',
          body: formData,
        })
          .then((resp) => {
            if (!resp.ok) {
              throw new Error('Erro HTTP ' + resp.status);
            }
            return resp.json();
          })
          .then((data) => {
            console.log('Resultado parser CV:', data);

            // Nome vindo do backend (se vier, sobrescreve a primeira linha)
            if (nomeInput && data.name) {
              nomeInput.value = data.name;
            }

            // Aqui depois a gente pode espalhar education_text / experience_text
            // para outros campos do formulário ou para os modais, se você quiser.

            alert('Currículo lido! Confira os dados antes de prosseguir.');
          })
          .catch((err) => {
            console.error(err);
            alert('Não foi possível processar o currículo. Tente enviar um arquivo .txt.');
          });
      });
    } else {
      console.log('Input de currículo não encontrado (#wpforms-27762-field_18)');
    }

        });
      });
    });
  });